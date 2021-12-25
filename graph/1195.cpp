#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
template <typename... T>
void debug(T&&...) {}
#endif
 
static const auto IOSetup = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // std::cout << std::setprecision(6) << std::fixed;
    return nullptr;
}();
 
using ll = long long;
using ld = long double;
 
using namespace std;
 
template <typename T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
 
template <class T>
auto dijkstra(const vector<vector<pair<int, T>>>& g, int s) {
    std::vector d(g.size(), std::numeric_limits<T>::max());
    std::vector prv(g.size(), -1);
    min_heap<std::pair<T, int>> rh;
    rh.emplace(d[s] = 0, s);
    while (!rh.empty()) {
        auto [dv, v] = rh.top();
        rh.pop();
        if (dv != d[v]) continue;
        for (auto&& [to, w] : g[v]) {
            if (d[to] > dv + w) {
                d[to] = dv + w;
                rh.emplace(d[to], to);
                prv[to] = v;
            }
        }
    }
    return std::make_pair(d, prv);
}
 
int main() {
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, m;
        cin >> n >> m;
        vector<vector<pair<int, ll>>> g(n), g_r(n);
        vector<tuple<int, int, ll>> edges;
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u, --v;
            g[u].emplace_back(v, w);
            g_r[v].emplace_back(u, w);
            edges.emplace_back(u, v, w);
        }
        auto [d1, prv1] = dijkstra(g, 0);
        auto [d2, prv2] = dijkstra(g_r, n - 1);
        auto inf = numeric_limits<ll>::max();
        ll ans = inf;
        for (auto [u, v, w] : edges) {
            if (d1[u] == inf || d2[v] == inf) continue;
            ans = min(ans, d1[u] + d2[v] + w / 2);
        }
        cout << ans << '\n';
    }
}
