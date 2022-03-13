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
        vector<int> indeg(n), outdeg(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            ++indeg[v];
            ++outdeg[u];
        }
        bool works = true;
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                if (indeg[i] != outdeg[i] - 1) works = false;
            } else if (i == n - 1) {
                if (indeg[i] != outdeg[i] + 1) works = false;
            } else {
                if (indeg[i] != outdeg[i]) works = false;
            }
        }
        EulerTour<true> e(g);
        if (!works) {
            cout << "IMPOSSIBLE\n";
        } else {
            auto path = e.get_tour();
            if ((int)path.size() == m + 1) {
                for (auto v : path) cout << v + 1 << ' ';
                cout << '\n';
            } else {
                cout << "IMPOSSIBLE\n";
            }
        }
    }
}

