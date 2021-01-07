#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<string> a(n);

    for (auto &x : a) cin >> x;

    vector<vector<int>> dp(n, vector<int>(m));

    for (int i = 0; i < m; ++i) {
        dp[0][i] = a[0][i] == '.';
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '.') dp[i][j] = dp[i - 1][j] + 1;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> &a = dp[i];
        stack<int> s;
        vector<int> prevpos(m, -1), nextpos(m, m);
        for (int i = 0; i < m; ++i) {
            while (!s.empty() && a[s.top()] >= a[i]) {
                s.pop();
            }
            if (!s.empty()) {
                prevpos[i] = s.top();
            }
            s.push(i);
        }
        stack<int>().swap(s);
        for (int i = m - 1; ~i; --i) {
            while (!s.empty() && a[s.top()] > a[i]) {
                s.pop();
            }
            if (!s.empty()) {
                nextpos[i] = s.top();
            }
            s.push(i);
        }
        for (int j = 0; j < m; ++j) {
            ans = max(ans, (dp[i][j] * (nextpos[j] - prevpos[j] - 1)));
        }
    }

    cout << ans << '\n';

    return 0;
}
