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
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, k;
        cin >> n >> k;
        if (ll(k) * k + 1 <= n) {
            cout << "IMPOSSIBLE\n";
        } else {
            vector<int> ans(n);
            int runs = (n + k - 1) / k;
            int ptr = 0;
            for (int i = 0; i < runs; ++i) {
                int run_begin = max(-n, -(i + 1) * k);
                int run_end = -i * k - 1;
                int cur = run_begin;
                while (cur <= run_end) ans[ptr++] = cur++;
            }
            for (auto& x : ans) x += n + 1;
            for (auto x : ans) cout << x << ' ';
            cout << '\n';
        }
    }
}
 
