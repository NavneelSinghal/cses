#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
// #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
 
#include <bits/stdc++.h>
 
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
 
using ll = int64_t;
 
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
    int t = 1;
    // cin >> t;
    while (t--) {
        int n, X;
        cin >> n >> X;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        vector<pair<int, int>> dp(1 << n, {n + 1, 0});
        dp[0] = {1, 0};
        for (int mask = 1; mask < (1 << n); ++mask) {
            int cur = mask;
            while (cur) {
                int i = __builtin_ctz(cur);
                auto [x, y] = dp[mask ^ (1 << i)];
                y += a[i];
                if (y > X) x++, y = a[i];
                ckmin(dp[mask], make_pair(x, y));
                cur ^= (cur & -cur);
            }
        }
        cout << dp[(1 << n) - 1].first << '\n';
    }
    return 0;
}
