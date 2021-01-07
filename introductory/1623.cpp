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
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    int max = 1 << (n);
    int mndiff = 1e18;
    for (int mask = 0; mask < max; mask++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j))
                sum += a[j];
            else
                sum -= a[j];
        }
        sum = abs(sum);
        mndiff = min(mndiff, sum);
    }
    cout << mndiff << endl;
    return 0;
}
