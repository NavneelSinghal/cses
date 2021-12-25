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
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n);
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            g[a - 1].push_back(b - 1);
        }
        vector<int> visited(n), order;
        auto dfs = [&](const auto& self, int u) -> void {
            visited[u] = 1;
            for (auto v : g[u]) {
                if (!visited[v]) self(self, v);
            }
            order.push_back(u);
        };
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) dfs(dfs, i);
        }
        reverse(begin(order), end(order));
        constexpr int inf = -int(1e9);
        vector<int> ans(n, inf);
        ans[n - 1] = 0;
        for (int i = n - 1; i >= 0; --i) {
            for (auto v : g[order[i]]) {
                ans[order[i]] = max(ans[order[i]], 1 + ans[v]);
            }
        }
        if (ans[0] < 0) {
            cout << "IMPOSSIBLE\n";
        } else {
            debug(ans, g);
            cout << ans[0] + 1 << '\n';
            int i = 0;
            cout << 1 << ' ';
            while (i != n - 1) {
                for (auto u : g[i]) {
                    if (ans[u] == ans[i] - 1) {
                        i = u;
                        break;
                    }
                }
                cout << i + 1 << ' ';
            }
            cout << '\n';
        }
    }
}
