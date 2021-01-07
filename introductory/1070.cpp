#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
#define int ll

signed main() {
    int n;
    cin >> n;
    if (n == 1)
        cout << 1 << endl;
    else if (n <= 3)
        cout << "NO SOLUTION" << endl;
    else if (n == 4)
        cout << "2 4 1 3\n";
    else {
        for (int i = (n / 2); i >= 1; i--) cout << 2 * i << " ";
        for (int i = (n / 2); i >= 0; i--)
            if (2 * i + 1 <= n) cout << 2 * i + 1 << " ";
    }
}
