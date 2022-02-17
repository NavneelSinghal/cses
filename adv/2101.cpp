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
        vector<pair<int, int>> edges(m);
        for (auto& [u, v] : edges) {
            cin >> u >> v;
            --u, --v;
        }
        vector<pair<int, int>> queries(q);
        for (auto& [u, v] : queries) {
            cin >> u >> v;
            --u, --v;
        }
        // initially
        // left = 0
        // right = m + 1
        vector<int> left(q, 0), right(q, m + 1);
        vector<vector<int>> queries_at_mid(m + 1);  // mid is in [1, m]
        for (int i = 0; i < q; ++i) queries_at_mid[(m + 1) / 2].push_back(i);
        int completed = 0;
        while (completed < q) {
            dsu dsu(n);
            for (int i = 0; i < m; ++i) {
                dsu.union_sets(edges[i].first, edges[i].second);
                int day = i + 1;
                for (auto query_index : queries_at_mid[day]) {
                    if (dsu.find_set(queries[query_index].first) ==
                        dsu.find_set(queries[query_index].second)) {
                        right[query_index] = day;
                    } else {
                        left[query_index] = day;
                    }
                }
            }
            vector<vector<int>> queries_at_mid_new(m + 1);
            completed = 0;
            for (int i = 0; i < q; ++i)
                if (left[i] + 1 < right[i])
                    queries_at_mid_new[(left[i] + right[i]) / 2].push_back(i);
                else
                    completed++;
            queries_at_mid = move(queries_at_mid_new);
        }
        for (int i = 0; i < q; ++i) {
            if (queries[i].first == queries[i].second) {
                cout << 0 << '\n';
            } else {
                assert(left[i] + 1 == right[i]);
                cout << (right[i] == m + 1 ? -1 : right[i]) << '\n';
            }
        }
    }
}

