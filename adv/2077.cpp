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
        int n, m;
        cin >> n >> m;
        vector<basic_string<int>> g(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u] += v;
            g[v] += u;
        }

        vector<int> tin(n), low(n);
        vector<bool> visited(n);
        int timer = 0;
        vector<bool> is_cutpoint(n);
        auto dfs = [&](const auto& self, int v, int p) -> void {
            visited[v] = true;
            tin[v] = low[v] = ++timer;
            int children = 0;
            for (int to : g[v]) {
                if (to == p) continue;
                if (visited[to]) {
                    low[v] = min(low[v], tin[to]);
                } else {
                    self(self, to, v);
                    low[v] = min(low[v], low[to]);
                    if (low[to] >= tin[v] && p != -1) is_cutpoint[v] = true;
                    ++children;
                }
            }
            if (p == -1 && children > 1) is_cutpoint[v] = true;
        };

        vector<int> cutpoints;
        for (int i = 0; i < n; ++i)
            if (!tin[i]) dfs(dfs, i, -1);
        for (int i = 0; i < n; ++i)
            if (is_cutpoint[i]) cutpoints.push_back(i);
        cout << cutpoints.size() << '\n';
        for (auto u : cutpoints) cout << u + 1 << ' ';
        cout << '\n';
    }
}

