#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
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
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x, --x;
        functional_graph_processor f(a);
        for (int i = 0; i < n; ++i)
            cout << f.depth[i] + (int)f.cycle[f.cycle_id[f.root[i]]].size()
                 << " \n"[i == n - 1];
    }
}

