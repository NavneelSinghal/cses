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
 
struct point {
    ll num, den;
    point(ll x, ll y) {
        auto g = gcd(x, y);
        num = x / g;
        den = y / g;
        if (den < 0) num *= -1, den *= -1;
    }
    point(ll x) {
        num = x;
        den = 1;
    }
    bool operator<(const point& other) const {
        return __int128(num) * other.den < __int128(other.num) * den;
    }
    friend ostream& operator<<(ostream& os, const point& p) {
        return os << p.num << '/' << p.den;
    }
};
 
constexpr ll linf = 1e18L;
 
struct line {
    ll a, b;
    ll eval(ll x) { return a * x + b; }
    point intersect(const line& other) const {
        assert(a != other.a);
        return point{other.b - b, a - other.a};
    }
    friend ostream& operator<<(ostream& os, const line& p) {
        return os << p.a << "x + " << p.b;
    }
};
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
 
        int n;
        cin >> n;
        vector<ll> s(n + 1), f(n + 1);
        cin >> f[0];
        for (int i = 1; i <= n; ++i) cin >> s[i];
        for (int i = 1; i <= n; ++i) cin >> f[i];
 
        // dp[i] = min time to kill ith monster
        // dp[i] = min_j dp[j] + f[j] * s[i]
        // dp[0] = 0
 
        // maintain lines L_i = f[i] * x + dp[i]
        // slopes decreasing
        // queries go from left to right
 
        // so we can maintain the upper convex hull
 
        // line, point
        deque<pair<line, point>> d{{line{f[0], 0}, {-linf}}};
 
        // keep lines sorted by slope in decreasing order
        // assumes that we add lines in decreasing order of slope
        auto add_line = [&](const line& l) -> void {
            if (d.back().first.a == l.a) {
                if (d.back().first.b <= l.b)
                    return;
                else
                    d.pop_back();
            }
            while (!d.empty() &&
                   !(d.back().second < d.back().first.intersect(l)))
                d.pop_back();
            if (d.empty()) {
                d.emplace_back(l, point{-linf});
            } else {
                auto pt = d.back().first.intersect(l);
                d.emplace_back(l, pt);
            }
        };
 
        vector<ll> dp(n + 1);
 
        // either just binsearch
        // or two pointers
 
        // binsearch
        for (int i = 1; i <= n; ++i) {
            auto it = lower_bound(
                rbegin(d), rend(d), pair{line{0, 0}, point{s[i]}},
                [](const pair<line, point>& a, const pair<line, point>& b) {
                    return b.second < a.second;
                });
            dp[i] = it->first.eval(s[i]);
            add_line(line{f[i], dp[i]});
        }
 
        cout << dp[n] << '\n';
    }
}
