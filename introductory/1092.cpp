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
    int x = n * (n + 1) / 2;
    if (x % 2 != 0)
        cout << "NO";
    else {
        cout << "YES\n";
        int req = x / 2;
        vector<int> v;
        vector<bool> used(n + 1, false);
        int u = n;
        while (req) {
            while (used[u] || req < u) u--;
            req -= u;
            used[u] = true;
            v.push_back(u);
        }
        cout << v.size() << endl;
        for (auto u : v) cout << u << " ";
        cout << endl;
        cout << n - v.size() << endl;
        for (int i = 1; i <= n; i++) {
            if (!used[i]) cout << i << " ";
        }
    }
}
