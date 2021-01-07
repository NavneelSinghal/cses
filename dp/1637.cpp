#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i <= n; ++i) {
        int cur = i;
        int temp;
        while (cur) {
            temp = cur % 10;
            if (temp) g[i].push_back(i - temp);
            cur /= 10;
        }
    }

    vector<int> steps(n + 1, 1e9);

    queue<int> q;
    q.push(n);
    steps[n] = 0;

    while (!q.empty()) {
        int m = q.front();
        q.pop();
        if (m == 0) {
            cout << steps[m] << '\n';
            return 0;
        }
        for (auto v : g[m]) {
            if (steps[v] == 1e9) {
                steps[v] = 1 + steps[m];
                q.push(v);
            }
        }
    }

    assert(false);

    return 0;
}
