#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int a, b;
    cin >> a >> b;

    int g = __gcd(a, b);
    a /= g;
    b /= g;

    vector<vector<int>> dp(a + 1, vector<int>(b + 1));

    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            if (i == j) {
                dp[i][j] = 1;
                continue;
            } else {
                dp[i][j] = 1e9;
                for (int k = 1; k + k <= i; ++k) {
                    dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j]);
                }
                for (int k = 1; k + k <= j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k]);
                }
            }
        }
    }

    cout << dp[a][b] - 1 << '\n';
}
