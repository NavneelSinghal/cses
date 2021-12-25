#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif
 
using namespace std;
 
using ll = int64_t;
using ld = long double;
 
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
 
namespace hashing {
    using ull = std::uint64_t;
    static const ull FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();
 
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
        ull operator()(T v) const {
            ull x = v + 0x9e3779b97f4a7c15 + FIXED_RANDOM;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
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
 
template <class T>
struct SparseFenwick2D {
    int n, m;
    __gnu_pbds::gp_hash_table<
        int, __gnu_pbds::gp_hash_table<int, T, hashing::custom_hash<int>>,
        hashing::custom_hash<int>>
        t;
    SparseFenwick2D(int n, int m) : n(n), m(m) {}
    T query(int i, int j) {
        T s = 0;
        for (int x = i; x > 0; x -= x & (-x)) {
            auto& tx = t[x];
            for (int y = j; y > 0; y -= y & (-y)) s += tx[y];
        }
        return s;
    }
    T query(int i1, int j1, int i2, int j2) {
        return query(i2, j2) - query(i2, j1 - 1) + query(i1 - 1, j1 - 1) -
               query(i1 - 1, j2);
    }
    void update(int i, int j, T v) {
        for (int x = i; x <= n; x += x & (-x)) {
            auto& tx = t[x];
            for (int y = j; y <= n; y += y & (-y)) tx[y] += v;
        }
    }
};
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, q;
        cin >> n >> q;
        SparseFenwick2D<ll> f(n, n);
        vector<string> s(n);
        for (auto& x : s) cin >> x;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (s[i][j] == '*') f.update(i + 1, j + 1, 1);
        while (q--) {
            int type;
            cin >> type;
            if (type == 1) {
                int x, y;
                cin >> x >> y;
                bool is_tree = (s[x - 1][y - 1] == '*');
                f.update(x, y, 1 - 2 * is_tree);
                s[x - 1][y - 1] = (is_tree ? '.' : '*');
            } else {
                int x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                cout << f.query(x1, y1, x2, y2) << '\n';
            }
        }
    }
}
