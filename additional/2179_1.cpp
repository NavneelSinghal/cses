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
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(20) << fixed;
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
            g[v].push_back(u);
        }
        vector<int> tin(n, -1);
        vector<pair<int, int>> edges;
        int timer = 0;
        // returns whether u -> p or not
        const auto dfs = [&](const auto& self, int u, int p) -> int {
            tin[u] = timer++;
            int out = 0;
            for (auto v : g[u]) {
                if (v == p) continue;
                if (tin[v] != -1) {
                    if (tin[v] > tin[u]) {
                        // goes downwards
                        edges.emplace_back(u, v);
                        out ^= 1;
                    }
                } else {
                    if (self(self, v, u)) {
                        // v -> u
                        edges.emplace_back(v, u);
                    } else {
                        edges.emplace_back(u, v);
                        out ^= 1;
                    }
                }
            }
            return out;
        };
        bool works = true;
        for (int i = 0; i < n; ++i) {
            if (tin[i] == -1 && dfs(dfs, i, -1)) {
                works = false;
                break;
            }
        }
        if (works) {
            for (auto [u, v] : edges) {
                cout << u + 1 << ' ' << v + 1 << '\n';
            }
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }
}
 
