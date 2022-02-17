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

        // note: this is also optimal binary search tree problem
        // can be solved in O(n log n) using
        // https://en.wikipedia.org/wiki/Garsia%E2%80%93Wachs_algorithm
        // but we use DP

        int n;
        cin >> n;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;
        vector<ll> pre(n);
        partial_sum(begin(a), end(a), begin(pre));
        auto cost = [&](int l, int r) {
            // [l, r)
            return pre[r - 1] - (l == 0 ? 0 : pre[l - 1]);
        };

        vector<vector<ll>> dp(n,
                              vector<ll>(n + 1, numeric_limits<ll>::max() / 4));
        // naive:
        // for (int i = 0; i < n; ++i) dp[i][i + 1] = 0;
        // for (int len = 2; len <= n; ++len) {
        //     for (int i = 0; i + len <= n; ++i) {
        //         const int j = i + len;
        //         auto& x = dp[i][j];
        //         for (int k = i + 1; k < j; ++k) x = min(x, dp[i][k] +
        //         dp[k][j]); x += cost(i, j);
        //     }
        // }

        // claim: cost(i, j) satisfies quadrangle inequality and monotonicity

        // proof:
        // monotonicity -> easy since all weights are non-negative
        // quadrangle: cost(a, c) + cost(b, d) <= cost(a, d) + cost(b, c)
        // in fact equality holds

        // so we can use knuth optimization
        // (https://codeforces.com/blog/entry/8219)

        vector<vector<int>> min_k(n, vector<int>(n + 1));
        for (int i = 0; i < n; ++i) dp[i][i + 1] = 0;

        // rather than iterating over len, we can also iterate as follows
        // makes it faster
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 2; j <= n; ++j) {
                auto& x = dp[i][j];
                auto& idx = min_k[i][j];
                const int k_left = min_k[i][j - 1] ?: i + 1;
                const int k_right = min_k[i + 1][j] ?: j - 1;
                for (int k = k_left; k <= k_right; ++k) {
                    ll val = dp[i][k] + dp[k][j];
                    if (x > val) x = val, idx = k;
                }
                x += cost(i, j);
            }
        }

        cout << dp[0][n] << '\n';
    }
}

