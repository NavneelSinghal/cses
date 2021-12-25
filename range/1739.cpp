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
 
// 1-based indexing
template <class T>
struct Fenwick2D {
    int n, m;
    vector<vector<T>> t;
    Fenwick2D(int n, int m) : n(n), m(m), t(n + 1, vector<T>(m + 1)) {}
    T query(int i, int j) {
        T s = 0;
        for (int x = i; x > 0; x -= x & (-x))
            for (int y = j; y > 0; y -= y & (-y)) s += t[x][y];
        return s;
    }
    T query(int i1, int j1, int i2, int j2) {
        return query(i2, j2) - query(i2, j1 - 1) + query(i1 - 1, j1 - 1) -
               query(i1 - 1, j2);
    }
    void update(int i, int j, T v) {
        for (int x = i; x <= n; x += x & (-x))
            for (int y = j; y <= n; y += y & (-y)) t[x][y] += v;
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
        Fenwick2D<ll> f(n, n);
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
