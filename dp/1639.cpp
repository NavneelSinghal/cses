#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s, t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 1e9));

    for (int i = 0; i < n; ++i) dp[i][0] = i;
    for (int j = 0; j < m; ++j) dp[0][j] = j;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i] == t[j]) {
                dp[i + 1][j + 1] = dp[i][j];
            }
            dp[i + 1][j + 1] =
                min(dp[i + 1][j + 1],
                    1 + min({dp[i][j], dp[i][j + 1], dp[i + 1][j]}));
        }
    }

    cout << dp[n][m] << '\n';
}
