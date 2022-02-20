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
        if (scc.size() > 1) {
            cout << "NO\n";
            cout << scc[1][0] + 1 << ' ' << scc[0][0] + 1 << '\n';
        } else {
            cout << "YES\n";
        }
    }
}

