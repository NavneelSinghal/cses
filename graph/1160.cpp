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
 
// https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Graph_Theory/Special_Graphs/functional_graph_processor.sublime-snippet
// fixed a typo (cycle.size() -> c.size())
struct functional_graph_processor {
    int n;
 
    vector<vector<int>> cycle;  // main cycles
 
    // id of the cycle it belongs to, -1 if not part of one
    vector<int> cycle_id;
    vector<int> cycle_pos;  // position in the cycle, -1 if not part of one
    vector<int> prev;  // previous vertex in the cycle, -1 if not part of one
 
    // size of the weakly connected component of the i-th main cycle
    vector<int> size;
 
    vector<int> root;   // first reachable node in the main cycle
    vector<int> depth;  // # of edges from the main cycle
 
    // forest of arborescences of reversed edges not on the main cycle
    vector<vector<int>> arb_forest;
 
    functional_graph_processor(const vector<int>& next)
        : n((int)next.size()),
          cycle_id(n, -1),
          cycle_pos(n, -1),
          root(n, -1),
          depth(n, -1),
          arb_forest(n) {
        vector<bool> was(n);
        for (auto u = 0; u < n; ++u) {
            if (was[u]) continue;
            int v = u;
            while (!was[v]) {
                was[v] = true;
                v = next[v];
            }
            if (!~depth[v]) {
                int w = v;
                vector<int> c;
                while (!~depth[w]) {
                    cycle_id[w] = (int)cycle.size();
                    cycle_pos[w] = (int)c.size();
                    c.push_back(w);
                    root[w] = w;
                    depth[w] = 0;
                    w = next[w];
                }
                cycle.push_back(c);
                size.push_back((int)cycle.size());
            }
            auto dfs = [&](auto self, int u) -> void {
                if (~depth[u]) return;
                int v = next[u];
                self(self, v);
                root[u] = root[v];
                ++size[cycle_id[root[u]]];
                depth[u] = depth[v] + 1;
                arb_forest[v].push_back(u);
            };
            dfs(dfs, u);
        }
    }
};
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        for (auto& x : a) cin >> x, --x;
        functional_graph_processor g(a);
 
        constexpr int LG = 19;
        array<vector<int>, LG> anc;
        anc.fill(vector<int>(n));
        anc[0] = a;
        for (int i = 1; i < LG; ++i)
            for (int j = 0; j < n; ++j) anc[i][j] = anc[i - 1][anc[i - 1][j]];
        auto ancestor = [&](int u, int k) {
            for (int i = 0; i < LG; ++i)
                if (k >> i & 1) u = anc[i][u];
            return u;
        };
 
        while (q--) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            int root_u = g.root[u];
            int root_v = g.root[v];
            if (g.cycle_id[root_u] != g.cycle_id[root_v]) {
                cout << -1 << '\n';
            } else if (root_u == root_v) {
                // same arborescence
                int ans = g.depth[u] - g.depth[v];
                if (ancestor(u, ans) != v) {
                    cout << -1 << '\n';
                } else {
                    cout << ans << '\n';
                }
            } else if (v == root_v) {
                // v on cycle, u in tree
                int ans = g.depth[u];
                int cycle_size = (int)g.cycle[g.cycle_id[root_u]].size();
                ans +=
                    (g.cycle_pos[root_v] - g.cycle_pos[root_u] + cycle_size) %
                    cycle_size;
                cout << ans << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
    }
}
