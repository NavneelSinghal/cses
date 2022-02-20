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

    int root(int v) {
        if (par[v] < 0) return v;
        return par[v] = root(par[v]);
    }

    bool join(int a, int b) {
        a = root(a);
        b = root(b);
        if (a != b) {
            if (par[b] < par[a]) swap(a, b);
            par[a] += par[b];
            par[b] = a;
            return true;
        }
        return false;
    }

    int size(int a) {
        a = root(a);
        return -par[a];
    }

    auto components() {
        vector<int> roots(n), size(n);
        for (int i = 0; i < n; ++i) {
            roots[i] = root(i);
            size[roots[i]]++;
        }
        vector<vector<int>> ans(n);
        for (int i = 0; i < n; ++i) ans[i].reserve(size[i]);
        for (int i = 0; i < n; ++i) ans[roots[i]].push_back(i);
        ans.erase(remove_if(ans.begin(), ans.end(),
                            [](const auto& v) { return v.empty(); }),
                  ans.end());
        return ans;
    }

    int count_components() {
        int ans = 0;
        for (int i = 0; i < n; ++i)
            if (root(i) == i) ans++;
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
        dsu dsu(n);
        int components = n;
        int max_size = 1;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            if (dsu.root(u) != dsu.root(v)) {
                --components;
                dsu.join(u, v);
                max_size = max(max_size, dsu.size(u));
            }
            cout << components << ' ' << max_size << '\n';
        }
    }
}

