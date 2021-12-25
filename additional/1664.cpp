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
 
template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
 
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
        int n, q;
        cin >> n >> q;
        vector<pair<int, int>> a(n);
        for (auto& [x, y] : a) cin >> x >> y;
        sort(begin(a), end(a), [](const auto& x, const auto& y) {
            if (x.second == y.second) return x.first < y.first;
            return x.second < y.second;
        });
        int mx = a.back().second;
        vector end_time(__lg(n) + 2, vector(mx + 1, mx + 1));
        for (auto [x, y] : a) ckmin(end_time[0][x], y);
        for (int lg = 0; lg < (int)end_time.size(); ++lg) {
            if (lg == 0) {
                for (int i = mx - 1; i >= 0; --i)
                    ckmin(end_time[0][i], end_time[0][i + 1]);
            } else {
                for (int i = mx - 1; i >= 0; --i) {
                    int t = end_time[lg - 1][i];
                    if (t <= mx) end_time[lg][i] = end_time[lg - 1][t];
                }
            }
        }
        while (q--) {
            int start, end;
            cin >> start >> end;
            int ans = 0;
            for (int i = (int)end_time.size() - 1; i >= 0; --i) {
                if (start <= mx && end_time[i][start] <= end) {
                    ans += (1 << i);
                    start = end_time[i][start];
                }
            }
            cout << ans << '\n';
        }
    }
}
 
