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
 
struct HLD_LCA {
    using graph = std::vector<std::vector<int>>;
    HLD_LCA(const graph &G, int root = 0)
        : N((int)G.size()),
          g(G),
          par(N),
          start(N),
          depth(N),
          sz(N),
          in_time(N) {
        par[root] = -1;
        timer = 0;
        dfs_sz(root);
        start[root] = root;
        dfs_hld(root);
    }
 
    bool is_anc(int u, int v) {
        return in_time[u] <= in_time[v] && in_time[u] + sz[u] >= in_time[v];
    }
 
    void dfs_sz(int u) {
        sz[u] = 1;
        for (auto &v : g[u]) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            g[v].erase(find(begin(g[v]), end(g[v]), u));
            dfs_sz(v);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
    void dfs_hld(int u) {
        in_time[u] = timer++;
        for (auto &v : g[u]) {
            start[v] = (v == g[u][0] ? start[u] : v);
            dfs_hld(v);
        }
    }
    int lca(int u, int v) {
        for (; start[u] != start[v]; v = par[start[v]])
            if (depth[start[u]] > depth[start[v]]) swap(u, v);
        return depth[u] < depth[v] ? u : v;
    }
 
    int N;
    graph g;
    std::vector<int> par, start, depth, sz, in_time;
    int timer;
};
 
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
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        HLD_LCA hld(g);
        vector<int> a(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            a[u]++;
            a[v]++;
            int l = hld.lca(u, v);
            a[l]--;
            if (hld.par[l] != -1) a[hld.par[l]]--;
        }
        auto dfs = [&](const auto& self, int u, int p) -> void {
            for (auto v : g[u]) if (v != p) self(self, v, u), a[u] += a[v];
        };
        dfs(dfs, 0, -1);
        for (auto x : a) cout << x << ' ';
        cout << '\n';
    }
}
