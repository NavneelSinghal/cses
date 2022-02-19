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

struct dominator_tree {
    vector<basic_string<int>> g, rg, bucket;
    vector<int> arr, par, rev, sdom, dom, dsu, label;
    int n, t;
    dominator_tree(int n)
        : g(n),
          rg(n),
          bucket(n),
          arr(n, -1),
          par(n),
          rev(n),
          sdom(n),
          dom(n),
          dsu(n),
          label(n),
          n(n),
          t(0) {}
    void add_edge(int u, int v) { g[u] += v; }
    void dfs(int u) {
        arr[u] = t;
        rev[t] = u;
        label[t] = sdom[t] = dsu[t] = t;
        t++;
        for (int w : g[u]) {
            if (arr[w] == -1) {
                dfs(w);
                par[arr[w]] = arr[u];
            }
            rg[arr[w]] += arr[u];
        }
    }
    int find(int u, int x = 0) {
        if (u == dsu[u]) return x ? -1 : u;
        int v = find(dsu[u], x + 1);
        if (v < 0) return u;
        if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
        dsu[u] = v;
        return x ? v : label[u];
    }
    vector<int> run(int root) {
        dfs(root);
        iota(dom.begin(), dom.end(), 0);
        for (int i = t - 1; i >= 0; i--) {
            for (int w : rg[i]) sdom[i] = min(sdom[i], sdom[find(w)]);
            if (i) bucket[sdom[i]] += i;
            for (int w : bucket[i]) {
                int v = find(w);
                if (sdom[v] == sdom[w])
                    dom[w] = sdom[w];
                else
                    dom[w] = v;
            }
            if (i > 1) dsu[i] = par[i];
        }
        for (int i = 1; i < t; i++) {
            if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
        }
        vector<int> outside_dom(n, -1);
        for (int i = 1; i < t; i++) outside_dom[rev[i]] = rev[dom[i]];
        return outside_dom;
    }
};

template <typename T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <class T, class G>
auto dijkstra(const G& g, int s) {
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
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, m;
        cin >> n >> m;
        vector<vector<pair<int, ll>>> g(n), g_rev(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u, --v;
            g[u].emplace_back(v, w);
            g_rev[v].emplace_back(u, w);
        }
        auto d1 = dijkstra<ll>(g, 0).first;
        auto d2 = dijkstra<ll>(g_rev, n - 1).first;
        dominator_tree d(n);
        for (int u = 0; u < n; ++u)
            for (auto [v, w] : g[u])
                if (d1[u] + w + d2[v] == d1[n - 1]) d.add_edge(u, v);
        auto dominators = d.run(0);
        vector<int> vertices;
        int u = n - 1;
        while (u != -1) {
            vertices.push_back(u + 1);
            u = dominators[u];
        }
        cout << vertices.size() << '\n';
        sort(begin(vertices), end(vertices));
        for (auto v : vertices) cout << v << ' ';
        cout << '\n';
    }
}

