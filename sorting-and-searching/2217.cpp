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
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for (auto& x : a) cin >> x, --x;
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[a[i]] = i;
        int ans = 1;
        for (int i = 0; i + 1 < n; ++i) ans += (pos[i] > pos[i + 1]);
        while (m--) {
            int i, j;
            cin >> i >> j;
            --j, --i;
            if (a[i] != a[j] + 1 && a[i] > 0)
                ans -= (pos[a[i] - 1] > pos[a[i]]);
            if (a[j] != a[i] + 1 && a[j] > 0)
                ans -= (pos[a[j] - 1] > pos[a[j]]);
            if (a[i] < n - 1) ans -= (pos[a[i]] > pos[a[i] + 1]);
            if (a[j] < n - 1) ans -= (pos[a[j]] > pos[a[j] + 1]);
            swap(a[i], a[j]);
            pos[a[i]] = i;
            pos[a[j]] = j;
            if (a[i] != a[j] + 1 && a[i] > 0)
                ans += (pos[a[i] - 1] > pos[a[i]]);
            if (a[j] != a[i] + 1 && a[j] > 0)
                ans += (pos[a[j] - 1] > pos[a[j]]);
            if (a[i] < n - 1) ans += (pos[a[i]] > pos[a[i] + 1]);
            if (a[j] < n - 1) ans += (pos[a[j]] > pos[a[j] + 1]);
            cout << ans << '\n';
        }
    }
}
