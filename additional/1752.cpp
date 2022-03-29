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

template <class T, class U = T>
bool ckmin(T& a, U&& b) {
    return b < a ? a = std::forward<U>(b), true : false;
}

template <class T, class U = T>
bool ckmax(T& a, U&& b) {
    return a < b ? a = std::forward<U>(b), true : false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, d;
        cin >> n >> d;
        vector<basic_string<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<int> depth(n);
        auto cmp = [&](int u, int v) {
            return depth[u] > depth[v];
        };
        vector<int> use(n);
        auto dfs = [&](auto self, int u, int p, int dep) -> int {
            basic_string<int> highest;
            depth[u] = dep;
            bool works = true;
            for (auto v : g[u]) {
                if (v == p) continue;
                highest.push_back(self(self, v, u, dep + 1));
                if (depth[highest.back()] - dep < d) works = false;
            }
            if (works) {
                use[u] = true;
                return u;
            }
            auto pop = [&] {
                int ans = highest[0];
                pop_heap(begin(highest), end(highest), cmp);
                highest.pop_back();
                return ans;
            };
            auto push = [&](int x) {
                highest.push_back(x);
                push_heap(begin(highest), end(highest), cmp);
            };
            make_heap(begin(highest), end(highest), cmp);
            while (highest.size() > 1) {
                int U = pop();
                int V = pop();
                if (depth[U] + depth[V] - 2 * dep < d) {
                    use[U] = false;
                    push(V);
                } else {
                    push(U);
                    push(V);
                    break;
                }
            }
            int U = highest[0];
            if (depth[U] - dep >= d) {
                use[u] = true;
                return u;
            }
            return highest[0];
        };
        dfs(dfs, 0, -1, 0);
        int sz = 0;
        for (int i = 0; i < n; ++i) sz += use[i];
        cout << sz << '\n';
        for (int i = 0; i < n; ++i)
            if (use[i]) cout << i + 1 << ' ';
        cout << '\n';
    }
}

