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
        int n, k;
        cin >> n >> k;
        vector<unsigned> a(n);
        string s;
        for (int i = 0; i < n; ++i) {
            cin >> s;
            int x = 0;
            for (auto c : s) x = x * 2 + (c - '0');
            a[i] = x;
        }
        int ans = 32;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                ans = min(ans, __builtin_popcount(a[i] ^ a[j]));
        cout << ans << '\n';
    }
}

