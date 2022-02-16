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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, k1, k2;
        cin >> n >> k1 >> k2;
        vector<basic_string<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u] += v;
            g[v] += u;
        }

        ll ans = 0;
        auto dfs = [&](const auto& self, int u, int p) -> deque<ll> {
            deque<ll> a{1};
            constexpr auto cnt_depth_atmost = [](const auto& a,
                                                 int depth) -> ll {
                if (depth < 0) return 0;
                if (depth + 1 >= (int)a.size()) return a[0];
                return a[0] - a[depth + 1];
            };
            for (auto v : g[u])
                if (v != p) {
                    auto b = self(self, v, u);
                    // b[i] = number of vertices at depth >= i
                    auto b_front = b[0];
                    b.push_front(b_front);  // offset by 1
                    // now combine
                    if (a.size() < b.size()) swap(a, b);
                    for (int i = 0; i + 1 < (int)b.size(); ++i)
                        b[i] -= b[i + 1];  // number of vertices at depth i
                    for (int i = 0; i < (int)b.size(); ++i)
                        ans += b[i] * (cnt_depth_atmost(a, k2 - i) -
                                       cnt_depth_atmost(a, k1 - i - 1));
                    for (int i = (int)b.size() - 1; i > 0; --i) b[i - 1] += b[i];
                    for (int i = 0; i < (int)b.size(); ++i) a[i] += b[i];
                }
            return a;
        };

        dfs(dfs, 0, -1);
        cout << ans << '\n';
    }
}

