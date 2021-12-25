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
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        string s;
        cin >> s;
        int n = (int)s.size();
        array<int, 4> freq{};
        vector<int> loc(256, -1);
        loc['A'] = 0;
        loc['T'] = 1;
        loc['G'] = 2;
        loc['C'] = 3;
        string ans;
        for (int i = 0; i < n; ++i) {
            freq[loc[s[i]]]++;
            if (freq[0] && freq[1] && freq[2] && freq[3]) {
                ans += s[i];
                freq = array<int, 4>{};
            }
        }
        string lookup = "ATGC";
        for (int i = 0; i < 4; ++i) {
            if (freq[i] == 0) {
                ans += lookup[i];
                break;
            }
        }
        cout << ans << '\n';
    }
}
