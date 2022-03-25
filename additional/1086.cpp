#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
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

template <typename I, typename P, bool b>
I bin_search_split(I l, I r, const P& predicate) {
    --l, ++r;
    while (r - l > 1) {
        auto mid = l + (r - l) / 2;
        if (predicate(mid))
            l = mid;
        else
            r = mid;
    }
    if constexpr (b) {
        return r;
    } else {
        return l;
    }
}

// returns first i in [l, r], p(i) false, and if none found, returns r + 1
template <typename I, typename P>
I find_first_false(I l, I r, const P& p) {
    return bin_search_split<I, P, true>(l, r, p);
}

// returns last i in [l, r], p(i) true, and if none found, returns l - 1
template <typename I, typename P>
I find_last_true(I l, I r, const P& p) {
    return bin_search_split<I, P, false>(l, r, p);
}

using ulll = __uint128_t;
using lll = __int128;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        constexpr auto count_digit_till = [](ll x, int d) -> lll {
            string s = to_string(x);
            int digits = (int)s.size();
            lll dp[20][2]{};
            lll cnt[20][2]{};

            // dp[i][0] = how many times d comes in an arbitrary suffix starting
            // from index i

            // dp[i][1] = how many times d comes in a suffix starting from index
            // i which is <= suffix of x starting from index i

            // cnt[i][0] = number of these numbers
            // cnt[i][1] = number of these numbers

            dp[digits][0] = 0;
            dp[digits][1] = 0;
            cnt[digits][0] = 1;
            cnt[digits][1] = 1;

            for (int i = digits - 1; i >= 0; --i) {
                // tight = 1
                int r = s[i] - '0';
                for (int j = 0; j <= r; ++j) {
                    bool b = (j == r);
                    dp[i][1] +=
                        dp[i + 1][b] + (j == d && d != 0 ? cnt[i + 1][b] : 0);
                    cnt[i][1] += cnt[i + 1][b];
                }
                // tight = 0
                for (int j = 0; j < 10; ++j) {
                    dp[i][0] += dp[i + 1][0] + (j == d ? cnt[i + 1][0] : 0);
                    cnt[i][0] += cnt[i + 1][0];
                }
            }

            return dp[0][1];
        };
        ll n;
        cin >> n;
        auto x = find_last_true(ll(1), ll(1e18), [&](ll m) {
            lll mx = 0;
            for (int i = 0; i < 10; ++i) mx = max(mx, count_digit_till(m, i));
            return mx <= n;
        });
        cout << x << '\n';
    }
}

