#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
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
        // return a + static_cast<Int>(generate_random_n(b - a));
        return std::uniform_int_distribution<Int>(a, b)(*this);
    }
    template <class Int>
    auto operator()(Int a) -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        // return static_cast<Int>(generate_random_n(a - 1));
        return std::uniform_int_distribution<Int>(0, a - 1)(*this);
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

RandomWyhash64 rng;

/* eppstein's algorithm (source: https://judge.yosupo.jp/submission/40026) */

template <typename T>
struct heap_node {
    std::array<heap_node*, 2> c;
    T key;

    friend heap_node* insert(heap_node* a, T new_key) {
        if (!a || new_key.first < a->key.first) {
            heap_node* n = new heap_node;
            n->c = {a, nullptr};
            n->key = new_key;
            return n;
        }
        a = new heap_node(*a);
        int z = rng() & 1;
        a->c[z] = insert(a->c[z], new_key);
        return a;
    }
};

template <typename T>
using min_priority_queue =
    std::priority_queue<T, std::vector<T>, std::greater<T>>;

std::vector<int64_t> k_shortest_paths(
    int N, std::vector<std::pair<std::array<int, 2>, int64_t>> edges, int st,
    int en, int K) {
    int M = int(edges.size());

    std::vector<std::vector<std::tuple<int, int, int64_t>>> radj(N);
    for (int e = 0; e < M; e++) {
        auto [x, l] = edges[e];
        auto [u, v] = x;
        radj[v].push_back({e, u, l});
    }

    std::vector<int64_t> dist(N, -1);
    std::vector<int> prvE(N, -1);
    std::vector<int> toposort;
    toposort.reserve(N);

    {
        min_priority_queue<std::pair<int64_t, int>> q;
        q.push({dist[en] = 0, en});

        while (!q.empty()) {
            auto [d, cur] = q.top();
            q.pop();
            if (d > dist[cur]) continue;
            toposort.push_back(cur);
            for (auto [e, nxt, l] : radj[cur]) {
                if (dist[nxt] == -1 || d + l < dist[nxt]) {
                    prvE[nxt] = e;
                    q.push({dist[nxt] = d + l, nxt});
                }
            }
        }
    }

    std::vector<std::vector<std::pair<int64_t, int>>> adj(N);
    for (int e = 0; e < M; e++) {
        auto& [x, l] = edges[e];
        const auto& [u, v] = x;
        if (dist[v] == -1) continue;
        assert(dist[u] != -1);

        l += dist[v] - dist[u];
        assert(l >= 0);

        if (e == prvE[u]) continue;

        adj[u].push_back({l, v});
    }
    for (int i = 0; i < N; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].push_back({-1, -1});  // Sentinel
    }

    using iter_t = decltype(adj[0].begin());
    using hnode = heap_node<std::pair<int64_t, iter_t>>;
    std::vector<hnode*> node_roots(N, nullptr);
    for (int cur : toposort) {
        if (cur != en) {
            assert(edges[prvE[cur]].first[0] == cur);
            int prv = edges[prvE[cur]].first[1];
            node_roots[cur] = node_roots[prv];
        } else {
            node_roots[cur] = nullptr;
        }

        const auto& [l, nxt] = adj[cur][0];
        if (nxt != -1) {
            node_roots[cur] = insert(node_roots[cur], {l, adj[cur].begin()});
        }
    }

    std::vector<std::pair<int64_t, int>> dummy_adj({{0, st}, {-1, -1}});

    std::vector<int64_t> res;
    res.reserve(K);
    min_priority_queue<std::tuple<int64_t, hnode*, iter_t>> q;
    q.push({dist[st], nullptr, dummy_adj.begin()});
    while (int(res.size()) < K && !q.empty()) {
        auto [l, start_heap, val_iter] = q.top();
        q.pop();
        res.push_back(l);
        int64_t elen = val_iter->first;
        if (next(val_iter)->second != -1) {
            q.push({l - elen + next(val_iter)->first, nullptr, next(val_iter)});
        }
        if (start_heap) {
            for (int z = 0; z < 2; z++) {
                auto nxt_start = start_heap->c[z];
                if (!nxt_start) continue;
                q.push({l - elen + nxt_start->key.first, nxt_start,
                        nxt_start->key.second});
            }
        }
        {
            int nxt = val_iter->second;
            auto nxt_start = node_roots[nxt];
            if (nxt_start) {
                q.push({l + nxt_start->key.first, nxt_start,
                        nxt_start->key.second});
            }
        }
    }
    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, m, k;
        cin >> n >> m >> k;
        vector<pair<array<int, 2>, ll>> edges(m);
        for (auto& [p, v] : edges) cin >> p[0] >> p[1] >> v, --p[0], --p[1];
        int a = 0;
        int b = n - 1;
        auto paths = k_shortest_paths(n + 2, edges, a, b, k);
        paths.resize(k, -1);
        for (auto v : paths) cout << v << ' ';
        cout << '\n';
    }
}

