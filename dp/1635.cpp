#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, x;
    cin >> n >> x;

    vector<int> c(n);

    for (auto &x : c) cin >> x;

    vector<int> dp(x + 1, 0);

    dp[0] = 1;

    for (int i = 0; i <= x; ++i) {
        for (auto &j : c) {
            if (i + j <= x) {
                add(dp[i + j], dp[i]);
            }
        }
    }

    cout << dp[x] << "\n";

    return 0;
}
