#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;
#define int ll

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string a;
    cin >> a;
    int fr[26] = {0};
    for (auto &c : a) fr[c - 'A']++;
    int numodd = 0;
    for (int i = 0; i < 26; i++) {
        numodd += fr[i] & 1;
    }
    if (numodd > 1)
        cout << "NO SOLUTION";
    else {
        if (numodd == 1) {
            char an;
            for (int i = 0; i < 26; i++) {
                if (fr[i] & 1) an = (char)(i + 'A');
            }
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < fr[i] / 2; j++) cout << (char)(i + 'A');
            }
            cout << an;
            for (int i = 25; i >= 0; i--) {
                for (int j = 0; j < fr[i] / 2; j++) cout << (char)(i + 'A');
            }
        } else {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < fr[i] / 2; j++) {
                    cout << (char)(i + 'A');
                }
            }
            for (int i = 25; i >= 0; i--) {
                for (int j = 0; j < fr[i] / 2; j++) {
                    cout << (char)(i + 'A');
                }
            }
        }
    }
}
