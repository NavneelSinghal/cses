#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, x;
    cin >> n >> x;

    vector<int> costs(n), pages(n);

    for (auto &c : costs) cin >> c;
    for (auto &p : pages) cin >> p;

    vector<int> dp(x + 1);

    int c = 0, p = 0;
    for (int i = 0; i < n; ++i) {
        c = costs[i];
        p = pages[i];
        for (int j = x; j >= c; --j) {
            dp[j] = max(dp[j], p + dp[j - c]);
        }
    }

    int ans = 0;
    for (int i = 0; i <= x; ++i) {
        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';
}
