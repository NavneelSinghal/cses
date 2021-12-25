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
 
std::pair<std::vector<int>, std::vector<int>> manacher(const std::string& s) {
    int n = (int)s.size();
    // d_odd[i] = length of palindrome centered at i
    // d_even[i] = length of palindrome centered at space before i
    std::vector<int> d_odd(n), d_even(n);
    // computing d_odd
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int len = (i > r) ? 1 : std::min(d_odd[l + r - i], r - i + 1);
        while (len <= i && i + len < n && s[i - len] == s[i + len]) ++len;
        d_odd[i] = len;
        --len;
        if (i + len > r) {
            l = i - len;
            r = i + len;
        }
    }
    // computing d_even
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int len = (i > r) ? 0 : std::min(d_even[l + r - i + 1], r - i + 1);
        while (len < i && i + len < n && s[i - len - 1] == s[i + len]) ++len;
        d_even[i] = len;
        --len;
        if (i + len > r) {
            l = i - len - 1;
            r = i + len;
        }
    }
    return {d_odd, d_even};
}
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        string s;
        cin >> s;
        auto [dodd, deven] = manacher(s);
        auto it_odd = max_element(begin(dodd), end(dodd));
        auto it_even = max_element(begin(deven), end(deven));
        if (2 * (*it_odd) - 1 > 2 * (*it_even)) {
            int start = int(it_odd - begin(dodd)) - *it_odd + 1;
            int len = 2 * *it_odd - 1;
            cout << s.substr(start, len) << '\n';
        } else {
            int start = int(it_even - begin(deven)) - *it_even;
            int len = 2 * *it_even;
            cout << s.substr(start, len) << '\n';
        }
    }
}
