// #ifndef LOCAL
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")    
#pragma GCC target("avx,avx2,bmi2")
// #endif
 
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
        auto work = [](const auto& self, int n, int k) -> int {
            if (n == 1) return 1;
            if (n == 2) {
                if (k == 1) {
                    return 2;
                } else {
                    return 1;
                }
            }
            int half = n / 2;
            if (k <= half) {
                return 2 * k;
            } else {
                int other_half = n - half;
                int ans = self(self, other_half, k - half);
                if (n & 1) {
                    return (2 * ans - 3 + n + 1) % (n + 1);
                } else {
                    return (2 * ans - 1 + n) % n;
                }
            }
        };
        cout << work(work, n, k) << '\n';
    }
}
