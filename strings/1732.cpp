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

// The prefix function for this string is defined as an array pi of length n,
// where pi[i] is the length of the longest proper prefix of the substring
// s[0...i] which is also a suffix of this substring.
vector<int> prefix_function(string s) {
    int n = (int)s.size();
    vector<int> pi(n);
    int j = 0;
    for (int i = 1; i < n; ++i) {
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
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
        auto pi = prefix_function(s);
        int pos = (int)s.size() - 1;
        vector<int> ans;
        while (pi[pos]) {
            ans.push_back(pi[pos]);
            pos = pi[pos] - 1;
        }
        reverse(begin(ans), end(ans));
        for (auto x : ans) cout << x << ' ';
        cout << '\n';
    }
}
