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
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> points(n);
        for (auto& [x, y] : points) cin >> x >> y;
        while (m--) {
            int x, y;
            bool on = false;
            cin >> x >> y;
            for (int i = 0, j = n - 1; i < n; j = i++) {
                auto [px, py] = points[i];
                auto [qx, qy] = points[j];
                int dx_1 = x - px;
                int dy_1 = y - py;
                int dx_2 = qx - x;
                int dy_2 = qy - y;
                if ((dx_1 == 0 && dy_1 == 0) || (dx_2 == 0 && dy_2 == 0)) {
                    on = true;
                    break;
                }
                if (((dx_1 <= 0 && dx_2 <= 0) || (dx_1 >= 0 && dx_2 >= 0)) && ((dy_1 <= 0 && dy_2 <= 0) || (dy_1 >= 0 && dy_2 >= 0))) {
                    int g_1 = gcd(dx_1, dy_1);
                    dx_1 /= g_1;
                    dy_1 /= g_1;
                    int g_2 = gcd(dx_2, dy_2);
                    dx_2 /= g_2;
                    dy_2 /= g_2;
                    if (dx_1 == dx_2 && dy_1 == dy_2) {
                        on = true;
                        break;
                    }
                }
            }
            if (on) {
                cout << "BOUNDARY\n";
            } else {
                bool inside = false;
                for (int i = 0, j = n - 1; i < n; j = i++) {
                    if ((points[i].second > y) == (points[j].second > y))
                        continue;
                    ll diff = points[j].second - points[i].second;
                    if (diff < 0) {
                        if ((x - points[i].first) * diff >
                            ll(points[j].first - points[i].first) *
                                (y - points[i].second))
                            inside = !inside;
                    } else {
                        assert(diff > 0);
                        if ((x - points[i].first) * diff <
                            ll(points[j].first - points[i].first) *
                                (y - points[i].second))
                            inside = !inside;
                    }
                }
                if (inside) {
                    cout << "INSIDE\n";
                } else {
                    cout << "OUTSIDE\n";
                }
            }
        }
    }
}

