#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 1e9 + 7;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dp(n, vector<int>(m + 1, 0));
    int x0;
    cin >> x0;
    if (x0 == 0) {
        for (int i = 1; i <= m; ++i) dp[0][i] = 1;
    } else {
        dp[0][x0] = 1;
    }
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        if (x == 0) {
            for (int j = 1; j <= m; j++) {
                for (int k = j - 1; k <= j + 1; k++) {
                    if (k >= 1 && k <= m) {
                        dp[i][j] += dp[i - 1][k];
                        dp[i][j] %= mod;
                    }
                }
            }
        } else {
            for (int k = x - 1; k <= x + 1; k++) {
                if (k >= 1 && k <= m) {
                    dp[i][x] += dp[i - 1][k];
                    dp[i][x] %= mod;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans += dp[n - 1][i];
        ans %= mod;
    }
    cout << ans << "\n";
}
