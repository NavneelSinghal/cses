#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int answer = 1e9;
    for (int i = 0; i < n; ++i) {
        vector<int> distance(n, -1);
        vector<int> parent(n, -1);
        queue<int> q;
        q.push(i);
        distance[i] = 0;
        bool found = false;
        while (!q.empty() && !found) {
            int v = q.front();
            q.pop();
            int d = distance[v];
            if (2 * d + 1 >= n) break;
            int p = parent[v];
            assert(distance[v] >= 0 && (parent[v] != -1 || v == i));
            for (auto u : g[v]) {
                if (distance[u] == -1) {
                    distance[u] = d + 1;
                    parent[u] = v;
                    q.push(u);
                } else if (u != p) {
                    answer = min(answer, d + 1 + distance[u]);
                }
            }
        }
    }

    if (answer == 1e9) {
        answer = -1;
    }

    cout << answer << '\n';

    return 0;
}
