#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s;
    int n;
    cin >> s;
    n = s.size();
    const int mod = 1e9 + 7;
    vector<int> dp(n + 1);
    vector<int> prev(26, -1);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        dp[i + 1] = dp[i] << 1;
        if (dp[i + 1] >= mod) dp[i + 1] -= mod;
        if (~prev[s[i] - 'a']) {
            dp[i + 1] -= dp[prev[s[i] - 'a']];
            if (dp[i + 1] < 0) dp[i + 1] += mod;
        }
        prev[s[i] - 'a'] = i;
    }
    cout << dp[n] - 1 << '\n';

    return 0;
}
