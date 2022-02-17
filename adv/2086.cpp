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
        int n, K;
        cin >> n >> K;
        vector<ll> a(n), pre(n);
        for (auto& x : a) cin >> x;
        partial_sum(begin(a), end(a), begin(pre));

        // [l, r)
        auto cost = [&](int l, int r) -> ll {
            auto sum = pre[r - 1] - (l == 0 ? 0 : pre[l - 1]);
            return sum * sum;
        };

        constexpr ll linf = 1e18;
        vector dp(K + 1, vector<ll>(n + 1, linf));
        // dp[i][j] = min cost if you divide [0, j) into i parts
        dp[0][0] = 0;

        // naive
        // for (int i = 1; i <= K; ++i) {
        //     // i parts
        //     for (int j = i; j <= n; ++j) {
        //         auto& x = dp[i][j];
        //         for (int l = i - 1; l < j; ++l)
        //             x = min(x, dp[i - 1][l] + cost(l, j));
        //     }
        // }

        // claim: if a[i][j] = min k such that dp[i][j] = dp[i - 1][k] + cost(k,
        // j) then we have a[i][j] <= a[i][j + 1]

        // proof: suppose not. let a[i][j] = k1, a[i][j + 1] = k2. then k2 < k1.
        // we can now construct a sol for the dp[i][j] by dropping the last
        // element of dp[i][j + 1] and using algebra we're done (by noting the
        // fact that extending dp[i][j]'s sol by the last element gives a valid
        // sol which may/may not be optimal

        // vector min_k(K + 1, vector<int>(n + 1, -1));

        // compute dp[i][j_left...j_right], given that we know that for all
        // these, k_left <= k <= k_right
        auto solve = [&](const auto& self, int i, int j_left, int j_right,
                         int k_left, int k_right) -> void {
            if (j_left > j_right) return;
            int j_mid = (j_left + j_right) / 2;
            // solve for j_mid naively now
            int k_best = k_left;
            // k < j
            int k_max = min(k_right, j_mid - 1);
            auto& x = dp[i][j_mid];
            for (int k = k_left; k <= k_max; ++k) {
                ll val = dp[i - 1][k] + cost(k, j_mid);
                if (val < x) x = val, k_best = k;
            }
            // propagate information about bounds further down
            self(self, i, j_left, j_mid - 1, k_left, k_best);
            self(self, i, j_mid + 1, j_right, k_best, k_right);
        };

        for (int i = 1; i <= K; ++i) solve(solve, i, i, n, i - 1, n - 1);

        cout << dp[K][n] << '\n';
    }
}

