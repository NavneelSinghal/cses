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

// kth roots from k = 1 to 64
// keep a global struct

struct KthRoot {
    using u32 = unsigned;
    using u64 = unsigned long long;
    vector<u64> pow[65];  // pow[k][x] = pow(x+2,k)  (k >= 4)
    KthRoot() {
        for (u32 t = 2; t < (1 << 16); t++) {
            u64 s = t * t;
            s = s * s;
            for (int k = 4;; k++) {
                pow[k].push_back(s);
                if (__builtin_umulll_overflow(s, t, &s)) break;
            }
        }
    }
    u64 sqrt(u64 n) const {
        if (n == -1ull) return u32(-1);
        u64 x = std::sqrt((double)n);
        return x * x > n ? x - 1 : x;
    }
    u64 cbrt(u64 n) const {
        u64 x = 0, y = 0;
        for (int s = 63; s >= 0; s -= 3) {
            x <<= 1;
            y = 3 * x * (x + 1) + 1;
            if (y <= (n >> s)) n -= y << s, ++x;
        }
        return x;
    }
    u64 operator()(u64 n, int k) {
        assert(k >= 1);
        if (k == 1 || n == 0) return n;
        if (k == 2) return sqrt(n);
        if (k == 3) return cbrt(n);
        auto ub = upper_bound(pow[k].begin(), pow[k].end(), n);
        return (ub - pow[k].begin()) + 1;
    }
} roots;

// all coordinate differences should fit in 32 bit integers
ull closest_pair(vector<pair<ll, ll>> pts) {
    int n = (int)pts.size();
    sort(pts.begin(), pts.end());
    set<pair<ll, ll>> s;
    ull best_dist = 8e18L;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        uint64_t d = roots.sqrt(best_dist);
        if (d * d != best_dist) ++d;
        if (j < n && pts[i].first - pts[j].first >= 0)
            while (j < n && uint64_t(pts[i].first - pts[j].first) >= d)
                s.erase({pts[j].second, pts[j].first}), ++j;

        auto it1 = s.lower_bound({pts[i].second - d, pts[i].first});
        auto it2 = s.upper_bound({pts[i].second + d, pts[i].first});

        for (auto it = it1; it != it2; ++it) {
            ull dx = abs(pts[i].first - it->second);
            ull dy = abs(pts[i].second - it->first);
            best_dist = min(best_dist, dx * dx + dy * dy);
        }
        s.insert({pts[i].second, pts[i].first});
    }
    return best_dist;
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
        vector<pair<ll, ll>> points;
        for (int i = 0; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            points.emplace_back(u, v);
        }
        cout << closest_pair(points) << '\n';
    }
}

