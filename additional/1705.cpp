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

auto block_cut_tree(const std::vector<std::vector<int>>& g) {
    int n = (int)g.size();
    std::vector<int> tin(n, -1), low(n, -1), is_cutpoint(n), stk;
    std::vector<std::vector<int>> components;
    int cutpoints = 0;
    int timer = 0;
    auto dfs = [&](auto self, int u, int p) -> void {
        tin[u] = low[u] = timer++;
        stk.push_back(u);
        for (int v : g[u]) {
            if (v == p) continue;
            if (tin[v] == -1) {
                self(self, v, u);
                low[u] = std::min(low[u], low[v]);
                if (low[v] >= tin[u]) {
                    is_cutpoint[u] = (tin[u] > 0 || tin[v] > 1);
                    std::vector<int> component{u};
                    while (component.back() != v)
                        component.push_back(stk.back()), stk.pop_back();
                    components.push_back(component);
                }
            } else
                low[u] = std::min(low[u], tin[v]);
        }
        if (is_cutpoint[u]) cutpoints++;
    };
    for (int u = 0; u < n; ++u)
        if (tin[u] == -1) dfs(dfs, u, -1);
    std::vector<std::vector<int>> forest;
    forest.reserve(cutpoints + components.size());
    std::vector<int> id(n, -1);
    for (int u = 0; u < n; ++u)
        if (is_cutpoint[u]) id[u] = (int)forest.size(), forest.emplace_back();
    for (auto& comp : components) {
        int node = (int)forest.size();
        forest.emplace_back();
        for (int u : comp)
            if (!is_cutpoint[u])
                id[u] = node;
            else
                forest[node].push_back(id[u]), forest[id[u]].push_back(node);
    }
    
    // id[i] = node in the block-cut forest corresponding to vertex i
    
    // components[i] = ith component (components also store cutpoints in them)
    
    // is_cutpoint[i] = 1 if i is a cutpoint, 0 otherwise
    
    // cutpoints = number of cutpoints (all nodes in block-cut forest numbered <
    // cutpoints are cutpoints)

    // forest = adjacency list for block-cut forest

    // one node for every cutpoint and one node for every component

    return std::tuple{forest, components, id, is_cutpoint, cutpoints};
}

struct HLD_LCA {
    using graph = std::vector<std::vector<int>>;
    HLD_LCA(const graph& G)
        : N((int)G.size()),
          g(G),
          par(N),
          start(N),
          depth(N),
          sz(N),
          in_time(N),
          root_of(N, -1) {
        timer = 0;
        for (int root = 0; root < N; ++root) {
            if (root_of[root] == -1) {
                par[root] = -1;
                dfs_sz(root, root);
                start[root] = root;
                dfs_hld(root);
            }
        }
    }

    bool is_anc(int u, int v) {
        return in_time[u] <= in_time[v] && in_time[u] + sz[u] > in_time[v];
    }

    void dfs_sz(int u, int r) {
        sz[u] = 1;
        root_of[u] = r;
        for (auto& v : g[u]) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            g[v].erase(find(begin(g[v]), end(g[v]), u));
            dfs_sz(v, r);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) std::swap(v, g[u][0]);
        }
    }
    void dfs_hld(int u) {
        in_time[u] = timer++;
        for (auto& v : g[u]) {
            start[v] = (v == g[u][0] ? start[u] : v);
            dfs_hld(v);
        }
    }
    int lca(int u, int v) {
        assert(root_of[u] == root_of[v]);
        for (; start[u] != start[v]; v = par[start[v]])
            if (depth[start[u]] > depth[start[v]]) std::swap(u, v);
        return depth[u] < depth[v] ? u : v;
    }
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    int N;
    graph g;
    std::vector<int> par, start, depth, sz, in_time, root_of;
    int timer;
};

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, m, q;
        cin >> n >> m >> q;
        vector<vector<int>> g(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        auto [forest, components, id, is_cutpoint, cutpoints] =
            block_cut_tree(g);
        HLD_LCA lca(forest);
        while (q--) {
            int a, b, c;
            cin >> a >> b >> c;
            --a, --b, --c;
            if (a == c || b == c) {
                cout << "NO\n";
                continue;
            }
            int na = id[a];
            int nb = id[b];
            int nc = id[c];
            if (lca.root_of[na] == lca.root_of[nb]) {
                if (is_cutpoint[c] && lca.root_of[nc] == lca.root_of[na]) {
                    if (lca.dist(na, nc) + lca.dist(nc, nb) ==
                        lca.dist(na, nb)) {
                        cout << "NO\n";
                    } else {
                        cout << "YES\n";
                    }
                } else {
                    cout << "YES\n";
                }
            } else {
                cout << "NO\n";
            }
        }
    }
}

