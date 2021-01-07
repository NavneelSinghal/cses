#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    vector<pair<int, int>> edges;
    set<pair<int, int>, greater<pair<int, int>>> s;

    for (auto &x : a) cin >> x;

    for (int i = 0; i < n; ++i) {
        if (a[i]) s.insert({a[i], i});
    }

    int cur, curdeg;
    bool possible = true;

    while (!s.empty()) {
        tie(curdeg, cur) = *s.begin();
        s.erase(s.begin());

        if (s.size() < curdeg) {
            possible = false;
            break;
        }

        vector<pair<int, int>> store;
        for (int i = 0; i < curdeg; ++i) {
            auto p = *s.begin();
            s.erase(p);
            edges.emplace_back(p.second, cur);
            p.first--;
            if (p.first) {
                store.push_back(p);
            }
        }

        for (auto p : store) {
            s.insert(p);
        }
    }

    if (!possible)
        cout << "IMPOSSIBLE\n";

    else {
        cout << edges.size() << '\n';
        for (auto &[x, y] : edges) {
            cout << x + 1 << ' ' << y + 1 << '\n';
        }
    }
}
