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
        vector dp(2, vector(x + 1, 0));
        vector<int> price(n), value(n), copies(n);
        for (auto& x : price) cin >> x;
        for (auto& x : value) cin >> x;
        for (auto& x : copies) cin >> x;
        for (int i = 0; i < n; ++i) {
            const int cnt = copies[i];
            const int w = price[i];
            const int v = value[i];
            for (int j = 0; j < w && j <= x; ++j) {
                // process every chain of j modulo w
                deque<pair<int, ll>> d;
                d.emplace_back(0, dp[(i - 1) & 1][j]);
                dp[i & 1][j] = dp[(i - 1) & 1][j];
                for (int l = 1; j + l * w <= x; ++l) {
                    // process j + l * w
                    ll y = dp[(i - 1) & 1][j + l * w] - v * l;
                    while (!d.empty() && d.back().second <= y) d.pop_back();
                    d.emplace_back(l, y);
                    while (l - d.front().first > cnt) d.pop_front();
                    dp[i & 1][j + l * w] = int(d.front().second + v * l);
                }
            }
        }
        cout << dp[(n - 1) & 1][x] << '\n';
    }
}

