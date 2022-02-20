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

using TYPE = ll;
struct pt {
    TYPE x, y;
};
int orientation(pt a, pt b, pt c) {
    TYPE v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if (v < 0) return -1;  // clockwise
    if (v > 0) return +1;  // counter-clockwise
    return 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int q;
        cin >> q;
        while (q--) {
            pt a, b, c;
            cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
            int o = orientation(a, b, c);
            if (o == -1) {
                cout << "RIGHT\n";
            } else if (o == 0) {
                cout << "TOUCH\n";
            } else {
                cout << "LEFT\n";
            }
        }
    }
}
