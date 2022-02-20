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
    int n = s.size();
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

// untested string matching
// use only with non-empty to_find
int count_matches(string to_find, string &text) {
    int n = (int)to_find.size();
    assert(n > 0);
    to_find += '#';
    int total_size = n + (int)text.size() + 1;
    vector<int> pi(n + 1);
    // j <= n always
    int matches = 0;
    for (int i = 1, j = 0; i < total_size; ++i) {
        // current character to be read
        char ch = ((i <= n) ? to_find[i] : text[i - n - 1]);
        // usual KMP loop to find the longest prefix that actually matches
        while (j && ch != to_find[j])
            j = pi[j - 1];
        // increment size if we found something that matches
        j += (ch == to_find[j]);
        // now j = pi[i] for the string to_find + '#' + pattern at this point
        if (i <= n)
            pi[i] = j;
        else if (j == n)
            matches++;  // this matches at position (i - 2 * n)
    }
    return matches;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        string text, to_find;
        cin >> text >> to_find;
        cout << count_matches(to_find, text) << '\n';
    }
}
