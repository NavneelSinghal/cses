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
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<basic_string<int>> g(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
 
        vector<int> d(n), sz(n);
        auto dfs_precompute = [&](const auto& self, int u, int p,
                                  int depth) -> void {
            d[u] = depth;
            sz[u] = 1;
            for (auto v : g[u])
                if (v != p) self(self, v, u, depth + 1), sz[u] += sz[v];
        };
        dfs_precompute(dfs_precompute, 0, -1, 0);
 
        vector<ll> ans(n);
        ans[0] = accumulate(begin(d), end(d), ll(0));
 
        auto dfs = [&](const auto& self, int u, int p) -> void {
            for (auto v : g[u])
                if (v != p) ans[v] = ans[u] + n - 2 * sz[v], self(self, v, u);
        };
 
        dfs(dfs, 0, -1);
        for (auto x : ans) cout << x << ' ';
        cout << '\n';
    }
}
 
