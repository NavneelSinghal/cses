#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi2")
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
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        int n;
        cin >> n;
        vector<int> c(n);
        for (auto& x : c) cin >> x;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<set<int>> col(n);
        vector<int> ans(n);
        auto dfs = [&](auto self, int u, int p) -> void {
            for (auto v : g[u])
                if (v != p) self(self, v, u);
            auto it = max_element(begin(g[u]), end(g[u]), [&](int i, int j) {
                return col[i].size() < col[j].size();
            });
            int bigchild = *it;
            col[u].swap(col[bigchild]);
            col[u].insert(c[u]);
            for (auto v : g[u])
                if (v != p && v != bigchild)
                    for (auto x : col[v]) col[u].insert(x);
            ans[u] = col[u].size();
        };
        dfs(dfs, 0, -1);
        for (int i = 0; i < n; ++i) cout << ans[i] << " \n"[i == n - 1];
    }
}
 
