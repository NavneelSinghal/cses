#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
#define int ll
signed main() {
    int n;
    cin >> n;
    while (n > 1) {
        cout << n << " ";
        if (n % 2)
            n = 3 * n + 1;
        else
            n /= 2;
    }
    cout << 1;
}
