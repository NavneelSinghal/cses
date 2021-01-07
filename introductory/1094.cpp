#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
#define int ll

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(n);
    b[0] = a[0];
    for (int i = 1; i < n; i++) {
        b[i] = max(b[i - 1], a[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += b[i] - a[i];
    }
    cout << ans;
}
