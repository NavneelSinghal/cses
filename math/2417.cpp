#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,bmi,bmi2")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif
 
using ll = int64_t;
using ld = long double;
 
using namespace std;
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        const int N = *max_element(begin(a), end(a));
        vector<int> freq(N + 1);
        for (auto x : a) freq[x]++;
        for (int i = 1; i <= N; ++i)
            for (int j = 2 * i; j <= N; j += i) freq[i] += freq[j];
        vector<ll> pairs(N + 1);
        for (int g = N; g >= 1; --g) {
            pairs[g] = freq[g] * 1LL * (freq[g] - 1) / 2;
            for (int i = 2 * g; i <= N; i += g) pairs[g] -= pairs[i];
        }
        cout << pairs[1] << '\n';
    }
}
