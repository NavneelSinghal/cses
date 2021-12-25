#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif
 
using namespace std;
 
using ll = int64_t;
using ld = long double;
 
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
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        cout << find_first_false(ll(1), ll(n) * n, [&n](ll x) {
            ll le = 0;
            for (int i = 1; i <= n; ++i) le += min(ll(n), x / i);
            return le <= (ll(n) * n) / 2;
        }) << '\n';
    }
}
