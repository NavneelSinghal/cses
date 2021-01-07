#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, x;
    cin >> n >> x;

    vector<int> c(n);

    for (auto &x : c) cin >> x;

    vector<int> dp(x + 1, 1e9);

    dp[0] = 0;

    for (int i = 0; i <= x; ++i) {
        for (auto &j : c) {
            if (i + j <= x) {
                dp[i + j] = min(dp[i + j], 1 + dp[i]);
            }
        }
    }

    if (dp[x] == 1e9) dp[x] = -1;

    cout << dp[x] << "\n";

    return 0;
}
