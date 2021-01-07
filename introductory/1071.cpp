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
        int x, y;
        cin >> y >> x;
        int a = max(y, x);
        int b = min(y, x);
        int s = (a - 1) * (a - 1);
        if (a == b)
            s += a;
        else if (a % 2 == 1) {
            if (x == a)
                s += a * 2 - y;
            else
                s += x;
        } else {
            if (y == a)
                s += a * 2 - x;
            else
                s += y;
        }
        cout << s << "\n";
    }
}
