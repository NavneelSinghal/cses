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

// z[i] is the length of the longest common prefix between s and the suffix of s
// starting at i.
std::vector<int> z_function(const std::string& s) {
    int n = (int)s.size();
    std::vector<int> z(n);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
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
        int n = (int)s.size();
        auto z = z_function(s);
        for (int len = 1; len <= n; ++len) {
            bool works = true;
            for (int i = len; i < n; i += len) {
                if (z[i] != n - i) {
                    works = false;
                    break;
                }
            }
            if (works) cout << len << ' ';
        }
        cout << '\n';
    }
}

