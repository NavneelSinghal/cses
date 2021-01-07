#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int sum = 0;
    vector<int> values(n);
    for (auto &x : values) cin >> x, sum += x;

    vector<char> possible(sum + 1, false);

    possible[0] = true;

    for (auto &v : values) {
        for (int s = sum; s >= v; --s) {
            possible[s] |= possible[s - v];
        }
    }

    vector<int> val;

    for (int i = 1; i <= sum; ++i) {
        if (possible[i]) val.push_back(i);
    }

    cout << val.size() << endl;
    for (auto v : val) cout << v << ' ';
    cout << endl;
}
