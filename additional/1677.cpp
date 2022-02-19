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
        int n, m, q;
        cin >> n >> m >> q;
        vector<pair<int, int>> edges;
        map<pair<int, int>, int> insert_time;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            if (u > v) swap(u, v);
            insert_time[{u, v}] = 0;
        }
        for (int i = 0; i < q; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            if (u > v) swap(u, v);
            insert_time[{u, v}] = q - i;
        }
        vector<pair<pair<int, int>, int>> edges_with_times(begin(insert_time),
                                                           end(insert_time));
        sort(begin(edges_with_times), end(edges_with_times),
             [](const auto& a, const auto& b) { return a.second < b.second; });
        vector<int> ans;
        dsu dsu(n);
        int components = n;
        for (auto [edge, t] : edges_with_times) {
            if (t > 0) ans.push_back(components);
            auto [u, v] = edge;
            if (dsu.find_set(u) != dsu.find_set(v)) {
                --components;
                dsu.union_sets(u, v);
            }
        }
        reverse(begin(ans), end(ans));
        for (auto x : ans) cout << x << ' ';
        cout << '\n';
    }
}

