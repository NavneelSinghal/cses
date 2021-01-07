#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

void remin(int &a, int b) {
    if (a <= b) return;
    a = b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> steps(n + 1, 1e9);
    steps[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int cur = i;
        while (cur) {
            remin(steps[i], 1 + steps[i - cur % 10]);
            cur /= 10;
        }
    }

    cout << steps[n] << "\n";

    return 0;
}
