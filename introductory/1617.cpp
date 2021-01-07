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
    int ans = 1;
    int x = 2;
    int mod = 1e9 + 7;
    while (n) {
        if (n & 1) {
            ans = (ans * x) % mod;
        }
        x = (x * x) % mod;
        n >>= 1;
    }
    cout << ans;
}
