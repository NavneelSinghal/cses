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

template <class T>
auto frequency(vector<T> a) {
    if (a.size() == 0) return vector<pair<T, int>>{};
    sort(begin(a), end(a));
    vector<pair<T, int>> ans{{a[0], 0}};
    int n = (int)a.size();
    for (int i = 0; i < n; ++i)
        if (i == 0 || a[i] == a[i - 1])
            ans.back().second++;
        else
            ans.emplace_back(a[i], 1);
    return ans;
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
        dsu dsu(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            dsu.union_sets(u, v);
        }
        auto components = dsu.components();
        vector<int> sizes;
        for (auto& c : components) sizes.push_back((int)c.size());
        auto f = frequency(sizes);
        debug(f);

        using B = bitset<1'00'001>;
        // now knapsack to check which sizes are possible

        auto compose = [&](const auto& self, const B& b, int k, int sz) -> B {
            if (k == 0) return b;
            if (k == 1) return b | (b << sz);
            int k2 = k / 2;
            if (k & 1) {
                auto b2 = self(self, b, k2, sz);
                return b2 | (b2 << ((k2 + 1) * sz));
            } else {
                auto b2 = self(self, b, k2, sz);
                return b2 | (b2 << (k2 * sz));
            }
        };

        B ans;
        ans[0] = true;

        for (auto [size, freq] : f) {
            /*
               note that if freq = 1
               ans = ans | (ans << size);
               if freq = 2,
               ans = (ans | (ans << size)) | ((ans | (ans << size)) << size)
                   = ans | (ans << size) | (ans << (2 * size))
               so for freq k,
               ans = ans | (ans << size) | ... | (ans << (k * size))
               f(ans, k) = ans | (ans << size) | ... | (ans << (k * size))
               f(ans, 2k) = f(ans, k) | (f(ans, k) << (k * size))
               f(ans, 2k + 1) = f(ans, k) | f(ans, k) << ((k + 1) * size)
               */
            ans = compose(compose, ans, freq, size);
        }

        string s(n, '0');
        for (int i = 1; i <= n; ++i) s[i - 1] += ans[i];
        cout << s << '\n';
    }
}

