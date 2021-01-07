#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
#define int ll

signed main() {
    string a;
    cin >> a;
    int len = 1;
    int lenhere = 1;
    int ind = 0;
    while (ind < (int)a.size() - 1) {
        if (a[ind] == a[ind + 1]) {
            lenhere++;
            len = max(len, lenhere);
        } else {
            len = max(len, lenhere);
            lenhere = 1;
        }
        ind++;
    }
    len = max(len, lenhere);
    cout << len;
}
