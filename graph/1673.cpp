#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v, cost;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<edge> edges(m);
    vector<vector<int>> g(n);

    for (int i = 0; i < m; ++i) {
        int u, v, x;
        cin >> u >> v >> x;
        --u, --v;
        edges[i].u = u;
        edges[i].v = v;
        edges[i].cost = -x;
        g[u].push_back(v);
    }

    const long long INF = 1e18;

    vector<long long> d(n, INF);

    d[0] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (auto &e : edges) {
            if (d[e.u] < INF) {
                if (d[e.v] > d[e.u] + e.cost) {
                    d[e.v] = max(-INF, d[e.u] + e.cost);
                }
            }
        }
    }

    vector<int> changed(n, 0);
    // 2n more iterations for the changes to be propagated in each negative
    // cycle for all elements n should work as well
    for (int i = 0; i < n; ++i) {
        for (auto &e : edges) {
            if (d[e.u] < INF) {
                if (d[e.v] > d[e.u] + e.cost) {
                    d[e.v] = max(-INF, d[e.u] + e.cost);
                    changed[e.v] = 1;
                }
            }
        }
    }

    vector<int> visited(n);

    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (auto v : g[u]) {
            if (!visited[v]) dfs(v);
        }
    };

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && changed[i]) dfs(i);
    }

    if (visited[n - 1]) {
        cout << -1 << endl;
        return 0;
    } else {
        cout << (-d[n - 1]) << endl;
        return 0;
    }
}
