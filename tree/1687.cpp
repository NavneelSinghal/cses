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
        constexpr int LG = 19;
        vector<vector<int>> anc(LG, vector<int>(n, -1));
        for (int i = 1; i < n; ++i) {
            int x;
            cin >> x;
            anc[0][i] = x - 1;
        }
        for (int h = 1; h < LG; ++h) {
            for (int i = 0; i < n; ++i) {
                int x = anc[h - 1][i];
                if (x == -1) continue;
                anc[h][i] = anc[h - 1][x];
            }
        }
        while (q--) {
            int v, k;
            cin >> v >> k;
            --v;
            for (int i = 0; i < LG && ~v; ++i)
                if (k >> i & 1) v = anc[i][v];
            cout << (v + 1 ?: -1) << '\n';
        }
    }
}

