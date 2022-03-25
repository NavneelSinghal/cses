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
 
auto find_scc(const std::vector<std::vector<int>>& g) {
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
    return std::tuple{scc, condensed_graph, component};
}
 
auto minimum_strong_connectivity_augmentation(
    const std::vector<std::vector<int>>& g) {
    std::vector<std::pair<int, int>> edges;
    int n = (int)g.size();
    if (n <= 1) return edges;
    std::vector<int> indegree(n), outdegree(n);
    for (int i = 0; i < n; ++i)
        for (auto v : g[i]) indegree[v]++, outdegree[i]++;
    std::vector<bool> visited(n);
    auto dfs = [&](const auto& self, int u) -> int {
        visited[u] = true;
        if (outdegree[u] == 0) return u;
        for (auto v : g[u]) {
            if (visited[v]) continue;
            auto w = self(self, v);
            if (w != -1) return w;
        }
        return -1;
    };
    std::vector<int> matched_sources, matched_sinks, unmatched_sources,
        unmatched_sinks;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0 && !visited[i]) {
            auto sink = dfs(dfs, i);
            if (sink != -1)
                matched_sources.push_back(i), matched_sinks.push_back(sink);
            else
                unmatched_sources.push_back(i);
        }
    }
    for (int i = 0; i < n; ++i)
        if (outdegree[i] == 0 && !visited[i]) unmatched_sinks.push_back(i);
    std::vector<int> sources = matched_sources, sinks = matched_sinks;
    std::copy(std::begin(unmatched_sources), std::end(unmatched_sources),
              std::back_inserter(sources));
    std::copy(std::begin(unmatched_sinks), std::end(unmatched_sinks),
              std::back_inserter(sinks));
    edges.reserve(std::max(sources.size(), sinks.size()));
    int k = (int)std::min(sources.size(), sinks.size());
    int matching = (int)matched_sources.size();
    edges.emplace_back(sinks[0], sources[matching - 1]);
    for (int i = 1; i < matching; ++i)
        edges.emplace_back(sinks[i], sources[i - 1]);
    for (int i = matching; i < k; ++i) edges.emplace_back(sinks[i], sources[i]);
    for (int i = k; i < (int)sources.size(); ++i)
        edges.emplace_back(sinks[0], sources[i]);
    for (int i = k; i < (int)sinks.size(); ++i)
        edges.emplace_back(sinks[i], sources[0]);
    assert(edges.size() > 0);
    return edges;
}
 
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
        vector<vector<int>> g(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
        }
        auto [scc, condensed_graph, component] = find_scc(g);
        auto edges = minimum_strong_connectivity_augmentation(condensed_graph);
        cout << (int)edges.size() << '\n';
        for (auto [u, v] : edges)
            cout << scc[u][0] + 1 << ' ' << scc[v][0] + 1 << '\n';
    }
}
