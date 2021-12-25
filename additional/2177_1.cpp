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
 
std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>,
           std::vector<int>>
find_scc(const std::vector<std::vector<int>>& g) {
    std::vector<int> val, z, component;
    std::vector<std::vector<int>> scc;
    int timer = 0, total_components = 0;
    const auto dfs = [&](const auto& self, int u) -> int {
        int low = val[u] = ++timer;
        int x;
        z.push_back(u);
        for (auto v : g[u])
            if (component[v] < 0)
                low = std::min(low, val[v] ? val[v] : self(self, v));
        if (low == val[u]) {
            scc.emplace_back();
            do {
                x = z.back();
                z.pop_back();
                component[x] = total_components;
                scc.back().push_back(x);
            } while (x != u);
            total_components++;
        }
        return val[u] = low;
    };
    int n = (int)g.size();
    val.assign(n, 0);
    component.assign(n, -1);
    timer = total_components = 0;
    for (int i = 0; i < n; ++i)
        if (component[i] < 0) dfs(dfs, i);
    std::reverse(std::begin(scc), std::end(scc));
    for (int i = 0; i < n; ++i)
        component[i] = total_components - 1 - component[i];
    std::vector<bool> seen(n);
    std::vector<std::vector<int>> condensed_graph(total_components);
    for (int i = 0; i < total_components; ++i) {
        for (auto u : scc[i])
            for (auto v : g[u])
                if (component[v] != i && !seen[component[v]])
                    condensed_graph[i].push_back(component[v]),
                        seen[component[v]] = true;
        for (auto v : condensed_graph[i]) seen[v] = false;
    }
    return {scc, condensed_graph, component};
}
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        int n, m;
        cin >> n >> m;
        using edge = pair<int, int>;
        vector<vector<pair<int, int>>> g(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].emplace_back(v, i);
            g[v].emplace_back(u, i);
        }
        vector<edge> edges;
        vector<bool> marked_edges(m);
        vector<bool> visited(n);
        const auto dfs = [&](const auto& self, int u) -> void {
            visited[u] = true;
            for (auto [v, i] : g[u]) {
                if (!marked_edges[i]) {
                    edges.emplace_back(u, v);
                    marked_edges[i] = true;
                    self(self, v);
                }
            }
        };
        vector<vector<int>> G(n);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(dfs, i);
            }
        }
        for (auto [u, v] : edges) G[u].push_back(v);
        auto [scc, _, __] = find_scc(G);
        if (scc.size() > 1) {
            cout << "IMPOSSIBLE\n";
        } else {
            for (auto [u, v] : edges) cout << u + 1 << ' ' << v + 1 << '\n';
        }
    }
}
 
