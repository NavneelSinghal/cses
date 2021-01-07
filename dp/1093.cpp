#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

void add(int& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

void mult(int& a, int b) { a = (1LL * a * b) % mod; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int sum = n * (n + 1) >> 1;

    if (sum & 1) {
        cout << 0 << endl;
        return 0;
    }

    sum >>= 1;

    vector<int> dp(sum + 1);
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = sum; j >= i; --j) {
            add(dp[j], dp[j - i]);
        }
    }

    mult(dp[sum], (mod + 1) / 2);

    cout << dp[sum] << endl;
}
