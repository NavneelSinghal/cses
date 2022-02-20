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
 
    int count_components() {
        int ans = 0;
        for (int i = 0; i < n; ++i)
            if (find_set(i) == i) ans++;
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
        int n, m;
        cin >> n >> m;
        vector<array<int, 3>> a(m);
        for (auto &[w, u, v] : a) cin >> u >> v >> w, --u, --v;
        sort(begin(a), end(a));
        dsu dsu(n);
        ll ans = 0;
        for (auto [w, u, v] : a) {
            if (dsu.find_set(u) == dsu.find_set(v)) continue;
            dsu.union_sets(u, v);
            ans += w;
        }
        if (dsu.count_components() > 1) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << ans << '\n';
        }
    }
}

