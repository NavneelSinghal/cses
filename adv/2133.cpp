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

namespace hashing {

    // #define USE_AES 0
    /* append to top
    #define USE_AES 1
    #if USE_AES
        #pragma GCC target("aes")
        #include <immintrin.h>
    #endif
    */

    using ll = std::int64_t;
    using ull = std::uint64_t;
    static const ull FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();

#if USE_AES
    std::mt19937 rd(FIXED_RANDOM);
    const __m128i KEY1{(ll)rd(), (ll)rd()};
    const __m128i KEY2{(ll)rd(), (ll)rd()};
#endif

    template <class T, class D = void>
    struct custom_hash {};

    // https://www.boost.org/doc/libs/1_55_0/doc/html/hash/combine.html
    template <class T>
    inline void hash_combine(ull& seed, const T& v) {
        custom_hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b97f4a7c15 + (seed << 12) + (seed >> 4);
    };

    // http://xorshift.di.unimi.it/splitmix64.c
    template <class T>
    struct custom_hash<
        T, typename std::enable_if<std::is_integral<T>::value>::type> {
        ull operator()(T _x) const {
            ull x = _x;
#if USE_AES
            // implementation defined till C++17, defined from C++20
            __m128i m{ll(ull(x) * 0xbf58476d1ce4e5b9ULL), (ll)FIXED_RANDOM};
            __m128i y = _mm_aesenc_si128(m, KEY1);
            __m128i z = _mm_aesenc_si128(y, KEY2);
            return z[0];
#else
            x += 0x9e3779b97f4a7c15 + FIXED_RANDOM;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
#endif
        }
    };

    template <class T>
    struct custom_hash<T,
                       std::void_t<decltype(std::begin(std::declval<T>()))>> {
        ull operator()(const T& a) const {
            ull value = FIXED_RANDOM;
            for (auto& x : a) hash_combine(value, x);
            return value;
        }
    };

    template <class... T>
    struct custom_hash<std::tuple<T...>> {
        ull operator()(const std::tuple<T...>& a) const {
            ull value = FIXED_RANDOM;
            std::apply(
                [&value](T const&... args) {
                    (hash_combine(value, args), ...);
                },
                a);
            return value;
        }
    };

    template <class T, class U>
    struct custom_hash<std::pair<T, U>> {
        ull operator()(const std::pair<T, U>& a) const {
            ull value = FIXED_RANDOM;
            hash_combine(value, a.first);
            hash_combine(value, a.second);
            return value;
        }
    };

};  // namespace hashing

#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"

namespace pbds {
    using namespace __gnu_pbds;
#ifdef PB_DS_ASSOC_CNTNR_HPP
    template <class Key, class Value, class Hash>
    using unordered_map = gp_hash_table<
        Key, Value, Hash, std::equal_to<Key>, direct_mask_range_hashing<>,
        linear_probe_fn<>,
        hash_standard_resize_policy<hash_exponential_size_policy<>,
                                    hash_load_check_resize_trigger<>, true>>;
    template <class Key, class Hash>
    using unordered_set = pbds::unordered_map<Key, null_type, Hash>;
#endif
#ifdef PB_DS_TREE_POLICY_HPP
    template <typename T>
    using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag,
                             tree_order_statistics_node_update>;
    template <typename T>
    using ordered_multiset = tree<T, null_type, std::less_equal<T>, rb_tree_tag,
                                  tree_order_statistics_node_update>;
    template <class Key, class Value, class Compare = std::less<Key>>
    using ordered_map = tree<Key, Value, Compare, rb_tree_tag,
                             tree_order_statistics_node_update>;
    // find_by_order(k)  returns iterator to kth element starting from 0;
    // order_of_key(k) returns count of elements strictly smaller than k;
    // for ordered_multiset, lower_bound and upper_bound swap roles
#endif
}  // namespace pbds

struct dynamic_connectivity {
    struct undo_op {
        int x, y, y_data;
        undo_op() {}
        undo_op(int _x, int _y, int _y_data) : x(_x), y(_y), y_data(_y_data) {}
    };

    struct dc_union_find {
        // When data[x] < 0, x is a root and -data[x] is its tree size. When
        // data[x] >= 0, data[x] is x's parent.
        vector<int> data;
        int components = 0;
        dc_union_find(int n = 0) {
            if (n > 0) init(n);
        }
        void init(int n) {
            data.assign(n + 1, -1);
            components = n;
        }
        int find(int x) const {
            // Note that we don't use path compression since it doesn't play
            // well with undo operations.
            while (data[x] >= 0) x = data[x];
            return x;
        }
        bool unite(int x, int y, vector<undo_op>& undo_ops) {
            x = find(x);
            y = find(y);
            if (x == y) return false;
            if (-data[x] < -data[y]) swap(x, y);
            undo_ops.emplace_back(x, y, data[y]);
            data[x] += data[y];
            data[y] = x;
            components--;
            return true;
        }
        void undo(const undo_op& op) {
            components++;
            data[op.y] = op.y_data;
            data[op.x] -= data[op.y];
        }
    };

    static constexpr int INF = 1e9 + 5;

    struct query {
        // type: +1 = add, -1 = erase, 0 = answer
        int type, x, y, matching_index;

        query(int _type = -INF, int _x = -INF, int _y = -INF,
              int _matching_index = INF)
            : type(_type), x(_x), y(_y), matching_index(_matching_index) {}
    };

    vector<query> queries;
    pbds::unordered_map<pair<int, int>, int,
                        hashing::custom_hash<pair<int, int>>>
        seen_table;
    dc_union_find UF;
    vector<undo_op> undo_ops;
    vector<ll> answers;

    // When calling recurse(start, end), all of the edges that should exist for
    // the entire range [start, end) have already been united and are in
    // undo_ops.
    void recurse(int start, int end) {
        if (end - start <= 1) {
            if (end - start == 1 && queries[start].type == 0)
                answers.push_back(UF.components);
            return;
        }

        int mid = (start + end) / 2;
        size_t initial_size = undo_ops.size();

        // To recurse on [start, mid), unite all edges that occur before [start,
        // mid) and end within [mid, end).
        for (int i = mid; i < end; i++)
            if (queries[i].type == -1 && queries[i].matching_index < start)
                UF.unite(queries[i].x, queries[i].y, undo_ops);

        recurse(start, mid);

        while (undo_ops.size() > initial_size) {
            UF.undo(undo_ops.back());
            undo_ops.pop_back();
        }

        // To recurse on [mid, end), unite all edges that occur in [start, mid)
        // and end after [mid, end).
        for (int i = start; i < mid; i++)
            if (queries[i].type == +1 && queries[i].matching_index >= end)
                UF.unite(queries[i].x, queries[i].y, undo_ops);

        recurse(mid, end);

        while (undo_ops.size() > initial_size) {
            UF.undo(undo_ops.back());
            undo_ops.pop_back();
        }
    }

    void add_query() { queries.emplace_back(0); }

    void add_edge_op(int type, int x, int y) {
        assert(type == +1 || type == -1);
        if (x > y) swap(x, y);
        if (type == +1) {
            assert(seen_table.find({x, y}) == seen_table.end());
            seen_table[{x, y}] = (int)queries.size();
            queries.emplace_back(type, x, y, INF);
        } else {
            assert(seen_table.find({x, y}) != seen_table.end());
            int index = seen_table[{x, y}];
            seen_table.erase({x, y});
            queries[index].matching_index = (int)queries.size();
            queries.emplace_back(type, x, y, index);
        }
    }

    vector<ll> solve(int n) {
        UF.init(n);
        recurse(0, (int)queries.size());
        return answers;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        // refer: https://codeforces.com/blog/entry/15296

        int n, m, q;
        cin >> n >> m >> q;

        dynamic_connectivity D;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            D.add_edge_op(1, u, v);
        }
        D.add_query();
        for (int i = 0; i < q; ++i) {
            int t, u, v;
            cin >> t >> u >> v;
            --u, --v;
            D.add_edge_op(t == 1 ? 1 : -1, u, v);
            D.add_query();
        }
        auto ans = D.solve(n);
        for (auto x : ans) cout << x << ' ';
        cout << '\n';
    }
}

