#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
#define int ll
set<string> s;
void generate(string a, int i) {
    if (i == a.size())
        s.insert(a);
    else {
        for (int j = i; j < a.size(); j++) {
            swap(a[i], a[j]);
            generate(a, i + 1);
            swap(a[i], a[j]);
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string a;
    cin >> a;
    generate(a, 0);
    cout << s.size() << endl;
    for (auto x : s) cout << x << "\n";
}
