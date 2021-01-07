#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    long long sum = 0;
    cin >> n;

    vector<int> a(n);
    for (auto &x : a) cin >> x, sum += x;

    // dp[i][j] = answer when current array is [i..j - 1]

    long long dp[n + 1][n + 1];

    for (int i = 0; i <= n; ++i) dp[i][i] = 0;

    for (int len = 1; len <= n; ++len)
        for (int i = 0, j = len; j <= n; ++i, ++j)
            dp[i][j] = max(a[i] - dp[i + 1][j], a[j - 1] - dp[i][j - 1]);

    cout << (dp[0][n] + sum) / 2 << endl;
}
