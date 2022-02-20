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
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        for (auto& x : a) cin >> x, --x;
        constexpr int LG = 30;
        array<vector<int>, LG> anc;
        anc.fill(vector<int>(n));
        anc[0] = a;
        for (int i = 1; i < LG; ++i)
            for (int j = 0; j < n; ++j) anc[i][j] = anc[i - 1][anc[i - 1][j]];
        while (q--) {
            int u, k;
            cin >> u >> k;
            --u;
            for (int i = 0; i < LG; ++i)
                if (k >> i & 1) u = anc[i][u];
            cout << u + 1 << '\n';
        }
    }
}
