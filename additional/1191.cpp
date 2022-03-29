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

template <class T, class U = T>
bool ckmin(T& a, U&& b) {
    return b < a ? a = std::forward<U>(b), true : false;
}

template <class T, class U = T>
bool ckmax(T& a, U&& b) {
    return a < b ? a = std::forward<U>(b), true : false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;
        a.resize(2 * n);
        for (int i = 0; i < n; ++i) a[i + n] = a[i];
        vector<ll> pre(2 * n + 1);
        partial_sum(begin(a), end(a), begin(pre) + 1);
        vector<int> endpoint(n);
        for (int i = 0, r = 0; i < n; ++i) {
            while (r < 2 * n && pre[r] - pre[i] <= k) ++r;
            if (r > n)
                endpoint[i] = r - n - 1;
            else
                endpoint[i] = r - 1;
        }
        int start = 0;
        for (int i = 0; i < n; ++i) start = endpoint[start];
        rotate(begin(a), begin(a) + start, begin(a) + n);
        ll sum = 0;
        int id = 0;
        for (int i = 0; i < n; ++i) {
            if (sum + a[i] > k) {
                sum = a[i];
                ++id;
            } else {
                sum += a[i];
            }
        }
        cout << id + 1 << '\n';
    }
}

