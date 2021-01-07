#include <bits/stdc++.h>
using namespace std;

#define v vector

const int mod = 1e9 + 7;
void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    v<string> a(n);
    for (auto &x : a) cin >> x;

    v<v<int>> dp(n, v<int>(n));
    dp[0][0] = (a[0][0] == '.');

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == '.') {
                if (i) add(dp[i][j], dp[i - 1][j]);
                if (j) add(dp[i][j], dp[i][j - 1]);
            }
        }
    }

    cout << dp[n - 1][n - 1] << '\n';
}
