#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
#define int ll

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> dp(n + 1);
    for (int i = 1; i < n; i++) {
        dp[i + 1] = dp[i] + max(0ll, 8 * (i - 1));
        // cout<<dp[i]<<" ";
        cout << i * i * (i * i - 1) / 2 - dp[i] << endl;
    }
    cout << n * n * (n * n - 1) / 2 - dp[n] << endl;
}
