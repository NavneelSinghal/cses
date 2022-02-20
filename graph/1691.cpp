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

// assumes that degree of everything is even
class EulerTour {
   private:
    vector<vector<int>> g;
    vector<int> ei;
    bool d;

    void recTour(int i, vector<int>& que) {
        while (ei[i] < (int)g[i].size()) {
            int t = g[i][ei[i]];
            ++ei[i];
            if ((!d) && (ei[t] >= (int)g[t].size() || g[t][ei[t]] > i))
                continue;
            recTour(t, que);
        }
        que.push_back(i);
    }

   public:
    // dir = true if graph is directed
    EulerTour(const vector<vector<int>>& g_, bool dir = false)
        : g(g_), ei(g_.size(), 0), d(dir) {
        for (int i = 0; i < (int)g.size(); ++i) sort(g[i].begin(), g[i].end());
    }

    vector<int> getTour(int i = 0) {
        vector<int> res;
        recTour(i, res);
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
            ++deg[u];
            ++deg[v];
        }
        for (int i = 0; i < n; ++i) {
            if (deg[i] & 1) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
        EulerTour et(g, false);
        auto path = et.getTour();
        if ((int)path.size() == m + 1) {
            for (auto x : path) cout << x + 1 << ' ';
            cout << '\n';
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }
}

