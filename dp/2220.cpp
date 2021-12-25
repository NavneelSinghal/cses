#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
template <typename... T>
void debug(T&&...) {}
#endif
 
static const auto IOSetup = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // std::cout << std::setprecision(6) << std::fixed;
    return nullptr;
}();
 
using ll = long long;
using ld = long double;
 
using namespace std;
 
// when using integers, keep overflow in mind
template <class T, class F = multiplies<T>>
T pwr(T a, long long n, F op = multiplies<T>(), T e = {1}) {
    assert(n >= 0);
    T res = e;
    while (n) {
        if (n & 1) res = op(res, a);
        if (n >>= 1) a = op(a, a);
    }
    return res;
}
 
int main() {
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        auto compute = [](ll x) -> ll {
            if (x < 0) return 0;
            if (x == 0) return 1;
            // x > 0
            auto s = to_string(x);
            int n = (int)s.size();
            ll ans = (pwr(9LL, n) - 1) / 8;
            char prv = '0' + 10;
            for (int i = 0; i <= n; ++i) {
                if (i == n) {
                    ++ans;
                    break;
                }
                // everything till the (i - 1)th digit is the same
                // if smaller digit
                int digit = s[i] - '0';
                if (digit != 0) {
                    // digit >= 1
                    int rem = n - i - 1;
                    auto p = pwr(9LL, rem);
                    if (prv >= s[i]) {
                        ans += (digit - (i == 0)) * p;
                    } else {
                        if (prv == '0') {
                            ans += (digit - (i == 0)) * p;
                        } else {
                            ans += (digit - 1 - (i == 0)) * p;
                        }
                    }
                }
                // if same digit as prv
                if (s[i] != prv) {
                    prv = s[i];
                } else {
                    break;
                }
            }
            return ans;
        };
        ll a, b;
        cin >> a >> b;
        cout << compute(b) - compute(a - 1) << '\n';
    }
}
