#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

void add(int& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= 6; ++j) {
            if (i + j <= n) {
                add(dp[i + j], dp[i]);
            }
        }
    }

    cout << dp[n] << "\n";

    return 0;
}
