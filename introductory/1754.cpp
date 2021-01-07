#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
#define int ll

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int third = (a + b) / 3;
        int x = max(0ll, a - third);
        int y = max(0ll, b - third);
        if (a == 2 * x + y && b == 2 * y + x)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
