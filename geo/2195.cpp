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
bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool ccw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o > 0 || (include_collinear && o == 0);
}
void replace_with_convex_hull(vector<pt>& a, bool include_collinear = false) {
    if (a.size() == 1) return;
    sort(a.begin(), a.end(),
         [](pt a, pt b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); });
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == (int)a.size() - 1 || cw(p1, a[i], p2, include_collinear)) {
            while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1],
                                         a[i], include_collinear))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == (int)a.size() - 1 || ccw(p1, a[i], p2, include_collinear)) {
            while (down.size() >= 2 &&
                   !ccw(down[down.size() - 2], down[down.size() - 1], a[i],
                        include_collinear))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    if (include_collinear && up.size() == a.size()) {
        reverse(a.begin(), a.end());
        return;
    }
    a.clear();
    for (int i = 0; i < (int)up.size(); i++) a.push_back(up[i]);
    for (int i = (int)down.size() - 2; i > 0; i--) a.push_back(down[i]);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<pt> a(n);
        for (auto& [x, y] : a) cin >> x >> y;
        replace_with_convex_hull(a, true);
        cout << a.size() << '\n';
        for (auto [x, y] : a) cout << x << ' ' << y << '\n';
    }
}
