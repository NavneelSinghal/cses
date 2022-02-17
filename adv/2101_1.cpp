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

struct dsu {
    int n;
    vector<int> par;

    // negative - size
    dsu(int n) : n(n), par(n, -1) {}

    int find_set(int v) {
        if (par[v] < 0) return v;
        return par[v] = find_set(par[v]);
    }

    bool union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (par[b] < par[a]) swap(a, b);
            par[a] += par[b];
            par[b] = a;
            return true;
        }
        return false;
    }

    auto components() {
        vector<int> root(n), size(n);
        for (int i = 0; i < n; ++i) {
            root[i] = find_set(i);
            size[root[i]]++;
        }
        vector<vector<int>> ans(n);
        for (int i = 0; i < n; ++i) ans[i].reserve(size[i]);
        for (int i = 0; i < n; ++i) ans[root[i]].push_back(i);
        ans.erase(remove_if(ans.begin(), ans.end(),
                            [](const auto& v) { return v.empty(); }),
                  ans.end());
        return ans;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        // parallel binary search:
        // keep a dsu
        int n, m, q;
        cin >> n >> m >> q;
        vector<vector<pair<int, int>>> g(n);
        dsu dsu(n);
        // i + 1 = time of insertion
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            if (dsu.find_set(u) == dsu.find_set(v)) continue;
            dsu.union_sets(u, v);
            g[u].emplace_back(v, i + 1);
            g[v].emplace_back(u, i + 1);
        }

        vector<int> depth(n, -1);
        constexpr int LG = 19;
        vector table(LG, vector<pair<int, int>>(n, {-1, m + 1}));
        // table[h][u] = {2^h-th ancestor of u, max weight of edges on this
        // path}
        auto dfs = [&](auto self, int u, int p, int w, int d) -> void {
            if (p != -1) {
                table[0][u] = {p, w};
                for (int h = 1; h < LG; ++h) {
                    auto [x, mx] = table[h - 1][u];
                    if (x == -1) break;
                    table[h][u] = {table[h - 1][x].first,
                                   max(mx, table[h - 1][x].second)};
                }
            }
            depth[u] = d;
            for (auto [v, new_w] : g[u])
                if (v != p) self(self, v, u, new_w, d + 1);
        };

        for (int i = 0; i < n; ++i)
            if (depth[i] == -1) dfs(dfs, i, -1, -1, 0);

        auto query = [&](int u, int v) {
            if (dsu.find_set(u) != dsu.find_set(v)) return -1;
            if (depth[u] > depth[v]) swap(u, v);
            int k = depth[v] - depth[u];
            int ans = 0;
            for (int i = 0; i < LG; ++i) {
                if (k >> i & 1) {
                    auto [anc, mx] = table[i][v];
                    ans = max(mx, ans);
                    v = anc;
                }
            }
            if (u == v) return ans;
            for (int i = LG - 1; i >= 0; --i) {
                auto [U, mx_u] = table[i][u];
                auto [V, mx_v] = table[i][v];
                if (U != V) {
                    ans = max({ans, mx_u, mx_v});
                    u = U;
                    v = V;
                }
            }
            ans = max({ans, table[0][u].second, table[0][v].second});
            return ans;
        };

        for (int i = 0; i < q; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            cout << query(u, v) << '\n';
        }
    }
}

