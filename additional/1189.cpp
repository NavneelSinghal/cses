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
        int n;
        cin >> n;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;
        for (auto& x : a) {
            int y;
            cin >> y;
            x -= y;
        }
        vector<ll> diff(n);
        partial_sum(begin(a), begin(a) + n - 1, begin(diff) + 1);
        nth_element(begin(diff), begin(diff) + n / 2, end(diff));
        ll x = diff[n / 2];
        ll ans = 0;
        for (int i = 0; i < n; ++i) ans += abs(diff[i] - x);
        cout << ans << '\n';
    }
}

