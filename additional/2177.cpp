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
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        int n, m;
        cin >> n >> m;
        using edge = pair<int, int>;
        vector<vector<pair<int, int>>> g(n);
        vector<edge> edges;
        edges.reserve(m);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].emplace_back(v, i);
            g[v].emplace_back(u, i);
            edges.emplace_back(u, v);
        }
        vector<int> lowlink(n), tin(n, -1);
        vector<bool> marked_edges(m);
        int timer = 0;
        bool works = true;
        const auto dfs_tarjan = [&](const auto& self, int u) -> void {
            tin[u] = timer++;
            lowlink[u] = tin[u];
            for (auto [v, i] : g[u]) {
                if (marked_edges[i]) continue;
                marked_edges[i] = true;
                if (edges[i].first == v) swap(edges[i].first, edges[i].second);
                if (tin[v] == -1) {
                    self(self, v);  // forward edge
                    lowlink[u] = min(lowlink[u], lowlink[v]);
                    if (lowlink[v] > tin[u]) {
                        // edge i is a bridge
                        works = false;
                    }
                } else {
                    lowlink[u] = min(lowlink[u], tin[v]);
                }
            }
        };
        dfs_tarjan(dfs_tarjan, 0);
        if (timer < n || !works) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        for (auto [u, v] : edges) cout << u + 1 << ' ' << v + 1 << '\n';
    }
}

