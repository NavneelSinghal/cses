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
 
template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
 
template <class T, class U = T>
bool ckmin(T& a, U&& b) {
    return b < a ? a = std::forward<U>(b), true : false;
}
 
template <class T, class U = T>
bool ckmax(T& a, U&& b) {
    return a < b ? a = std::forward<U>(b), true : false;
}
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int root = 0;
        vector<int> leaves;
        for (int i = 0; i < n; ++i) {
            if ((int)g[i].size() > 1) {
                root = i;
            } else {
                leaves.push_back(i);
            }
        }
        int timer = 0;
        vector<int> tin(n);
        const auto dfs = [&](const auto& self, int u, int p) -> void {
            tin[u] = timer++;
            for (auto v : g[u])
                if (v != p) self(self, v, u);
        };
        dfs(dfs, root, -1);
        sort(begin(leaves), end(leaves),
             [&](int i, int j) { return tin[i] < tin[j]; });
        int l = (int)leaves.size();
        cout << (l + 1) / 2 << '\n';
        vector<pair<int, int>> edges;
        for (int i = 0; i < l / 2; ++i) {
            edges.emplace_back(leaves[i], leaves[i + l / 2]);
        }
        if (l & 1) edges.emplace_back(leaves.front(), leaves.back());
        for (auto [x, y] : edges) {
            cout << x + 1 << ' ' << y + 1 << '\n';
        }
    }
}

