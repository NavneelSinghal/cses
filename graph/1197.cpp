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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, m;
        cin >> n >> m;
        struct edge {
            int u, v;
            ll w;
        };
        vector<edge> edges(m);
        for (auto& [u, v, w] : edges) {
            cin >> u >> v >> w;
            --u, --v;
        }
        constexpr ll linf = 1e18L;
        vector<ll> d(n, linf);
        vector<int> p(n, -1);
        int modified = -1;
        for (int i = 0; i < n; ++i) {
            modified = -1;
            for (auto [u, v, w] : edges) {
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    p[v] = u;
                    modified = v;
                }
            }
        }
        if (modified == -1) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (int i = 0; i < n; ++i) modified = p[modified];
            int v = modified;
            vector<int> cycle{v};
            while (p[v] != modified) {
                v = p[v];
                cycle.push_back(v);
            }
            reverse(begin(cycle), end(cycle));
            for (auto u : cycle) cout << u + 1 << ' ';
            cout << cycle.front() + 1 << '\n';
        }
    }
}

