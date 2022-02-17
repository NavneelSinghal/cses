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
        int A = *max_element(begin(a), end(a));
        int bits = __lg(A) + 1;
        A = 1 << bits;
        vector<int> cnt_subset(A), cnt_supset(A);
        for (auto x : a) cnt_subset[x]++, cnt_supset[x]++;

        for (int bit = 0; bit < bits; ++bit) {
            for (int i = 0; i < A; ++i) {
                if (i >> bit & 1) {
                    cnt_subset[i] += cnt_subset[i ^ (1 << bit)];
                } else {
                    cnt_supset[i] += cnt_supset[i ^ (1 << bit)];
                }
            }
        }

        for (int i = 0; i < n; ++i)
            cout << cnt_subset[a[i]] << ' ' << cnt_supset[a[i]] << ' '
                 << n - cnt_subset[(~a[i]) & (A - 1)] << '\n';
    }
}

