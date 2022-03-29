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
        int n, x;
        cin >> n >> x;
        constexpr int X = 100000;
        vector dp(X + 1, 0);
        vector<int> price(n), value(n), copies(n);
        for (auto& x : price) cin >> x;
        for (auto& x : value) cin >> x;
        for (auto& x : copies) cin >> x;

        auto add = [&](int weight, int value) {
            for (int i = X; i >= weight; --i)
                ckmax(dp[i], dp[i - weight] + value);
        };

        for (int i = 0; i < n; ++i) {
            int cnt = copies[i];
            int w = price[i];
            int v = value[i];
            for (int j = 0; (1 << j) <= cnt; ++j)
                add(w * (1 << j), v * (1 << j)), cnt -= 1 << j;
            if (cnt) add(w * cnt, v * cnt);
        }

        cout << *max_element(begin(dp), begin(dp) + x + 1) << '\n';
    }
}

