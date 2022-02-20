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

auto find_scc(const std::vector<std::vector<int>>& g) {
    std::vector<int> val, z, component;
    std::vector<std::vector<int>> scc;
    int timer = 0, total_components = 0;
    const auto dfs = [&](const auto& self, int u) -> int {
        int low = val[u] = ++timer;
        int x;
        z.push_back(u);
        for (auto v : g[u])
            if (component[v] < 0)
                low = std::min(low, val[v] ? val[v] : self(self, v));
        if (low == val[u]) {
            scc.emplace_back();
            do {
                x = z.back();
                z.pop_back();
                component[x] = total_components;
                scc.back().push_back(x);
            } while (x != u);
            total_components++;
        }
        return val[u] = low;
    };
    int n = (int)g.size();
    val.assign(n, 0);
    component.assign(n, -1);
    timer = total_components = 0;
    for (int i = 0; i < n; ++i)
        if (component[i] < 0) dfs(dfs, i);
    std::reverse(std::begin(scc), std::end(scc));
    return scc;
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
            g[u].push_back(v);
        }
        auto scc = find_scc(g);
        if ((int)scc.size() == n) {
            cout << "IMPOSSIBLE\n";
        } else {
            int u = -1;
            for (auto comp : scc) {
                if (comp.size() > 1) {
                    u = comp[0];
                    break;
                }
            }
            // u is in a cycle
            vector<int> color(n), p(n, -1);
            int start = -1, finish = -1;
            auto dfs = [&](const auto& self, int u, int parent) -> void {
                p[u] = parent;
                color[u] = 1;
                for (auto v : g[u]) {
                    if (color[v] == 1) {
                        if (start == -1) {
                            start = u;
                            finish = v;
                        }
                    } else if (color[v] == 0) {
                        self(self, v, u);
                    }
                }
                color[u] = 2;
            };
            dfs(dfs, u, -1);
            int v = start;
            vector<int> cycle;
            while (v != finish) {
                cycle.push_back(v);
                v = p[v];
            }
            cycle.push_back(finish);
            cycle.push_back(cycle[0]);
            reverse(begin(cycle), end(cycle));
            cout << cycle.size() << '\n';
            for (auto v : cycle) {
                cout << v + 1 << ' ';
            }
            cout << '\n';
        }
    }
}
