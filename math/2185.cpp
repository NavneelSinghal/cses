#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif
 
static const auto IOSetup = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // std::cout << std::setprecision(6) << std::fixed;
    return nullptr;
}();
 
using ll = long long;
using ld = long double;
 
using namespace std;
 
template <typename T, typename U>
bool check_mult_overflow(T&& a, U&& b) {
    return __builtin_mul_overflow_p(a, b, (__typeof__(a + b))0);
}
template <typename T, typename U>
bool check_add_overflow(T&& a, U&& b) {
    return __builtin_add_overflow_p(a, b, (__typeof__(a + b))0);
}
template <typename T, typename U>
bool check_sub_overflow(T&& a, U&& b) {
    return __builtin_sub_overflow_p(a, b, (__typeof__(a + b))0);
}
 
int main() {
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        uint64_t n;
        int k;
        cin >> n >> k;
        vector<uint64_t> p(k);
        for (auto& x : p) cin >> x;
        uint64_t ans = 0;
        for (int i = 1; i < (1 << k); ++i) {
            uint64_t prod = 1;
            int parity = -1;
            for (int j = 0; j < k; ++j) {
                if (i >> j & 1) {
                    parity *= -1;
                    if (check_mult_overflow(prod, p[j])) {
                        prod = numeric_limits<uint64_t>::max();
                    } else {
                        prod *= p[j];
                    }
                }
            }
            ans += parity * (n / prod);
        }
        cout << ans << '\n';
    }
}
