#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC target("avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif
#include "bits/stdc++.h"
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

using namespace std;

template <class T, class D = void>
struct bigger_type {};
template <class T>
struct bigger_type<T, std::enable_if_t<sizeof(T) <= 4, void>> {
    using type = std::uint64_t;
};
template <class T>
struct bigger_type<T, std::enable_if_t<4 < sizeof(T) && sizeof(T) <= 8, void>> {
    using type = __uint128_t;
};

template <class T>
struct lehmer {
    using U = typename bigger_type<T>::type;
    using result_type = T;
    using state_type = U;
    state_type state;
    static constexpr T MAGIC =
        (sizeof(T) >= 8 ? 0xda942042e4dd58b5 : 0xe4dd58b5);
    static constexpr std::size_t shift_size = (sizeof(T) >= 8 ? 64 : 32);
    constexpr lehmer(state_type state_ = default_seed) : state{state_} {}
    constexpr result_type operator()() {
        state *= MAGIC;
        return state >> shift_size;
    }
    constexpr void seed(state_type s) { state = s; }
    static constexpr result_type min() {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() {
        return std::numeric_limits<result_type>::max();
    }
    constexpr friend bool operator==(const lehmer& a, const lehmer& b) {
        return a.state == b.state;
    }
    constexpr friend bool operator!=(const lehmer& a, const lehmer& b) {
        return a.state != b.state;
    }
    static constexpr state_type default_seed = 0;
};

template <class T>
struct wyhash {
    using U = typename bigger_type<T>::type;
    using result_type = T;
    using state_type = U;
    state_type state;
    static constexpr T MAGIC_INCREMENT =
        (sizeof(T) >= 8 ? 0x60bee2bee120fc15 : 0xe120fc15);
    static constexpr T MAGIC_MULTIPLY1 =
        (sizeof(T) >= 8 ? 0xa3b195354a39b70d : 0x4a39b70d);
    static constexpr T MAGIC_MULTIPLY2 =
        (sizeof(T) >= 8 ? 0x1b03738712fad5c9 : 0x12fad5c9);
    static constexpr std::size_t shift_size = (sizeof(T) >= 8 ? 64 : 32);

    constexpr wyhash(state_type state_ = default_seed) : state{state_} {}
    constexpr result_type operator()() {
        state += MAGIC_INCREMENT;
        U tmp = static_cast<U>(state) * MAGIC_MULTIPLY1;
        result_type m1 = static_cast<result_type>((tmp >> shift_size) ^ tmp);
        tmp = static_cast<U>(m1) * MAGIC_MULTIPLY2;
        result_type m2 = static_cast<result_type>((tmp >> shift_size) ^ tmp);
        return m2;
    }
    constexpr void discard(std::uint64_t steps) {
        state +=
            static_cast<state_type>(static_cast<U>(MAGIC_INCREMENT) * steps);
    }
    constexpr void seed(state_type s) { state = s; }
    static constexpr result_type min() {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() {
        return std::numeric_limits<result_type>::max();
    }
    constexpr friend bool operator==(const wyhash& a, const wyhash& b) {
        return a.state == b.state;
    }
    constexpr friend bool operator!=(const wyhash& a, const wyhash& b) {
        return a.state != b.state;
    }
    static constexpr state_type default_seed = 0;
};

template <class RNG>
struct Random : RNG {
    using RNG::operator();
    Random() : RNG(gen_seed()) {}

    static std::uint64_t gen_seed() {
        return std::chrono::steady_clock::now().time_since_epoch().count();
    }

    using T = typename RNG::result_type;
    using U = typename bigger_type<T>::type;
    static constexpr std::size_t shift_size = CHAR_BIT * sizeof(T);

    // generate random integer in [0, N]
    auto generate_random_n(const T N) {
        U product = static_cast<U>(operator()() - RNG::min()) * N;
        T lsb = static_cast<T>(product);
        if (lsb < N) {
            T threshold = -static_cast<T>(N) % static_cast<T>(N);
            while (lsb < threshold) {
                product = static_cast<U>(operator()() - RNG::min()) * N;
                lsb = static_cast<T>(product);
            }
        }
        return static_cast<T>(product >> shift_size);
    }
    template <class Int>
    auto operator()(Int a, Int b)
        -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        return a + static_cast<Int>(generate_random_n(b - a));
        // return std::uniform_int_distribution<Int>(a, b)(*this);
    }
    template <class Int>
    auto operator()(Int a) -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        return static_cast<Int>(generate_random_n(a - 1));
        // return std::uniform_int_distribution<Int>(0, a - 1)(*this);
    }
    template <class Real>
    auto operator()(Real a, Real b)
        -> std::enable_if_t<std::is_floating_point_v<Real>, Real> {
        return std::uniform_real_distribution<Real>(a, b)(*this);
    }
};

using RandomMersenne32 = Random<std::mt19937>;
using RandomLehmer32 = Random<lehmer<std::uint32_t>>;
using RandomWyhash32 = Random<wyhash<std::uint32_t>>;
using RandomMersenne64 = Random<std::mt19937_64>;
using RandomLehmer64 = Random<lehmer<std::uint64_t>>;
using RandomWyhash64 = Random<wyhash<std::uint64_t>>;

namespace treap {

    RandomLehmer32 rng;

    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        int size = 0;
        bool to_reverse = false;

        constexpr Node() : size{1}, to_reverse{false} {}
    };

    int size(Node* a) { return a ? a->size : 0; }
    bool to_reverse(Node* a) { return a ? a->to_reverse : false; }

    Node* parent(Node* a) { return a ? a->parent : nullptr; }

    // applies the lazy stuff to current position (i.e., does apply_update) and
    // pushes it down to children (i.e., does compose_update)
    // assumes a is not nullptr
    void push(Node* a) {
        if (a->to_reverse) {
            swap(a->left, a->right);
            if (a->left) a->left->to_reverse ^= 1;
            if (a->right) a->right->to_reverse ^= 1;
            a->to_reverse = false;
        }
    }

    // recomputes values from children
    // there might be lazy values that need to be propagated down in node a, but
    // we don't care about them as they need to be applied on the whole subarray
    // corresponding to the subtree of a, so whenever they are applied, they
    // will lead to the correct answer (as apply_update distributes over
    // combine_nodes)
    // assumes a is not nullptr
    void recalc(Node* a) {
        // size, value, sum, update, to_reverse
        a->size = 1;

        constexpr auto combine_into = [](const Node* a, const Node* b,
                                         Node* res) {
            int size = a->size + b->size;
            res->size = size;
        };

        if (a->left) push(a->left), combine_into(a->left, a, a);
        if (a->right) push(a->right), combine_into(a, a->right, a);
    }

    Node* root(Node* a) {
        while (parent(a)) a = parent(a);
        return a;
    }

    // takes a subtree and splits it into two subtrees
    // not necessary for it to have update = id_update
    [[nodiscard]] std::pair<Node*, Node*> split(Node* a, int in_left) {
        if (size(a) <= in_left) return {a, nullptr};
        // assert(a);
        push(a);
        // assert(!(a->parent));
        int size_left = size(a->left);
        if (size_left >= in_left) {
            if (a->left) a->left->parent = nullptr;
            auto [l, r] = split(a->left, in_left);
            a->left = r;
            if (r) r->parent = a;
            recalc(a);
            return {l, a};
        } else {
            if (a->right) a->right->parent = nullptr;
            auto [l, r] = split(a->right, in_left - size_left - 1);
            a->right = l;
            if (l) l->parent = a;
            recalc(a);
            return {a, r};
        }
    }

    // takes two nodes and merges them together
    // not necessary for them to have update = id_update
    [[nodiscard]] Node* merge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;
        // assert(!(a->parent));
        // assert(!(b->parent));
        if (rng(a->size + b->size) < b->size) {
            push(b);
            if (b->left) b->left->parent = nullptr;
            b->left = merge(a, b->left);
            if (b->left) b->left->parent = b;
            recalc(b);
            return b;
        } else {
            push(a);
            if (a->right) a->right->parent = nullptr;
            a->right = merge(a->right, b);
            if (a->right) a->right->parent = a;
            recalc(a);
            return a;
        }
    }

    // applies reverse to a node
    [[nodiscard]] Node* reverse(Node* a) {
        if (!a) return a;
        a->to_reverse ^= 1;
        return a;
    }

    template <class ostream>
    ostream& operator<<(ostream& os, Node* a) {
        dbg(a, os);
        return os;
    }

    void delete_treap(Node* a) {
        if (!a) return;
        delete_treap(a->left);
        delete_treap(a->right);
        delete a;
    }

}  // namespace treap

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<treap::Node> a(n);
        treap::Node* t = nullptr;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            --x;
            t = treap::merge(t, &a[x]);
        }
        vector<pair<int, int>> moves;
        array<treap::Node*, 1000> path_to_root;
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            treap::Node* cur = &a[i];
            while (cur) {
                path_to_root[cnt++] = cur;
                cur = treap::parent(cur);
            }
            for (int j = cnt - 1; j >= 0; --j) treap::push(path_to_root[j]);
            int pos = treap::size(a[i].left);
            for (int j = 0; j + 1 < cnt; ++j)
                if (path_to_root[j] == path_to_root[j + 1]->right)
                    pos += treap::size(path_to_root[j + 1]->left) + 1;
            if (pos == i) continue;
            moves.emplace_back(i + 1, pos + 1);
            auto [t12, t3] = treap::split(t, pos + 1);
            auto [t1, t2] = treap::split(t12, i);
            t2 = treap::reverse(t2);
            t = treap::merge(t1, treap::merge(t2, t3));
        }
        cout << moves.size() << '\n';
        for (auto [i, j] : moves) cout << i << ' ' << j << '\n';
    }
}

