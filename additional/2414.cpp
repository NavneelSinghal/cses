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
        int m = n * (n - 1) / 2;
        vector<int> b(m);
        for (auto& x : b) cin >> x;
        sort(begin(b), end(b));

        vector<int> a(n);
        // smallest = a[0] + a[1]
        // second smallest = a[0] + a[2]
        for (int i = 2; i < m; ++i) {
            int twice_a0 = b[0] + b[1] - b[i];
            if (twice_a0 % 2 == 1) continue;
            a[0] = twice_a0 / 2;
            a[1] = b[0] - a[0];
            if (a[0] > a[1] || a[0] <= 0) continue;
            bool works = true;
            multiset<int> s;
            for (int j = 0; j < m; ++j) s.insert(b[j]);
            for (int j = 1; j < n && works; ++j) {
                for (int k = 0; k < j - 1 && works; ++k) {
                    auto it = s.find(a[k] + a[j - 1]);
                    if (it == s.end()) {
                        works = false;
                        break;
                    }
                    s.erase(it);
                }
                a[j] = *s.begin() - a[0];
            }
            if (works) break;
        }
        for (auto x : a) cout << x << ' ';
        cout << '\n';
    }
}

