#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
#define int ll
signed main() {
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 0; i < n - 1; i++) {
        int x;
        cin >> x;
        sum += x;
    }
    cout << n * (n + 1) / 2 - sum;
}
