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

// use greater<> for forward lexicographical topological sort
vector<int> reverse_lexicographical_topological_sort(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> indeg(n), res;
    for (int u = 0; u < n; ++u)
        for (auto v : g[u]) ++indeg[v];
    priority_queue<int, vector<int>> q;
    for (int u = 0; u < n; ++u)
        if (!indeg[u]) q.push(u);
    while (!q.empty()) {
        int u = q.top();
        q.pop();
        res.push_back(u);
        for (auto v : g[u])
            if (!--indeg[v]) q.push(v);
    }
    return (int)res.size() == n ? res : vector<int>{};
}

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
            g[v].push_back(u);
        }
        auto scc = lexicographical_topological_sort(g);
        if ((int)scc.size() == 0) {
            cout << "IMPOSSIBLE\n";
        } else {
            reverse(begin(scc), end(scc));
            for (int i = 0; i < n; ++i) cout << scc[i] + 1 << ' ';
            cout << '\n';
        }
    }
}
