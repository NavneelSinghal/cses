#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
 
#include <bits/stdc++.h>
 
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
 
using ll = int64_t;
 
auto FindSCC(const vector<vector<int>> &G, int const Base = 0) {
    vector<vector<int>> SCC;
    vector<unsigned> S, P, depth(G.size());
    const auto dfs = [&](const auto &self, auto u) -> void {
        auto d = S.size();
        S.push_back(u);
        P.push_back(d + 1);
        depth[u] = d + 1;
        for (auto v : G[u]) {
            if (!depth[v])
                self(self, v);
            else
                while (P.back() > depth[v]) P.pop_back();
        }
        if (P.back() > d) {
            SCC.emplace_back(S.begin() + d, S.end());
            for (auto v : SCC.back()) depth[v] = -1;
            S.erase(S.begin() + d, S.end());
            P.pop_back();
        }
    };
    for (auto u = Base; u < G.size(); ++u)
        if (!depth[u]) dfs(dfs, u);
    reverse(SCC.begin(), SCC.end());
    return SCC;
}
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        vector<vector<int>> g(n);
        while (m--) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
        }
        auto scc = FindSCC(g);
        vector<int> scc_id(n);
        for (int i = 0; i < (int)scc.size(); ++i)
            for (auto x : scc[i]) scc_id[x] = i;
        vector<ll> store(n);
        for (int i = 0; i < n; ++i)
            store[scc_id[i]] += a[i];
        vector<set<int>> h(scc.size());
        for (int i = 0; i < n; ++i) {
            for (auto v : g[i]) {
                if (scc_id[v] != scc_id[i]) {
                    h[scc_id[i]].insert(scc_id[v]);
                }
            }
        }
        vector<ll> dp(scc.size());
        for (int i = (int)scc.size() - 1; i >= 0; --i) {
            ll mx = 0;
            for (auto v : h[i]) {
                mx = max(mx, dp[v]);
            }
            dp[i] = store[i] + mx;
        }
        cout << *max_element(begin(dp), end(dp)) << '\n';
    }
    return 0;
}
