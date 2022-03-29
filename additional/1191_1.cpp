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
        vector<int> endpoint(2 * n);
        for (int i = 0, r = 0; i < 2 * n; ++i) {
            while (r <= 2 * n && pre[r] - pre[i] <= k) ++r;
            endpoint[i] = r - 1;  // next subarray from endpoint[i]
        }
        int lgn = __lg(n) + 2;
        vector table(lgn, vector(2 * n, 2 * n));
        table[0] = endpoint;
        for (int h = 1; h < lgn; ++h) {
            for (int i = 0; i < 2 * n; ++i) {
                if (table[h - 1][i] == 2 * n) continue;
                table[h][i] = table[h - 1][table[h - 1][i]];
            }
        }
        int ans = n + 1;
        for (int i = 0; i < n; ++i) {
            int steps = 0;
            int cur = i;
            for (int h = lgn - 1; h >= 0; --h) {
                if (table[h][cur] < i + n) {
                    cur = table[h][cur];
                    steps |= (1 << h);
                }
            }
            ans = min(ans, steps + 1);
        }
        cout << ans << '\n';
    }
}

