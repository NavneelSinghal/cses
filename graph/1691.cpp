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

// finds euler tour, euler path in directed and undirected graphs
// assumes there exists such a path
// conditions:
// undirected:
//   tour: all degrees are even
//   path: all degrees are even except the degrees of endpoints
// directed:
//   tour: indegree = outdegree for everything
//   path: if starting, indeg = outdeg - 1, if ending, indeg = outdeg + 1, and
//         indeg = outdeg otherwise
template <bool is_directed = false>
class EulerTour {
   private:
    vector<vector<int>> g;
    vector<int> edge_ptr;

    void dfs_tour(int i, vector<int>& que) {
        while (edge_ptr[i] < (int)g[i].size()) {
            int t = g[i][edge_ptr[i]];
            ++edge_ptr[i];
            if ((!is_directed) &&
                (edge_ptr[t] >= (int)g[t].size() || g[t][edge_ptr[t]] > i))
                continue;
            dfs_tour(t, que);
        }
        que.push_back(i);
    }

   public:
    // dir = true if graph is directed
    EulerTour(const vector<vector<int>>& g_) : g(g_), edge_ptr(g_.size(), 0) {
        for (int i = 0; i < (int)g.size(); ++i) sort(g[i].begin(), g[i].end());
    }

    vector<int> get_tour(int i = 0) {
        vector<int> res;
        dfs_tour(i, res);
        reverse(begin(res), end(res));
        return res;
    }
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
        vector<int> deg(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
            ++deg[v];
            ++deg[u];
        }
        for (int i = 0; i < n; ++i) {
            if (deg[i] & 1) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
        EulerTour<false> et(g);
        auto path = et.get_tour();
        if ((int)path.size() == m + 1) {
            for (auto x : path) cout << x + 1 << ' ';
            cout << '\n';
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }
}

