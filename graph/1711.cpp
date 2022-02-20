#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC target("avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"

#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

using namespace std;

template <class T>
struct simple_queue {
    std::vector<T> payload;
    int pos = 0;
    void reserve(int n) { payload.reserve(n); }
    int size() const { return int(payload.size()) - pos; }
    bool empty() const { return pos == int(payload.size()); }
    void push(const T& t) { payload.push_back(t); }
    T& front() { return payload[pos]; }
    void clear() {
        payload.clear();
        pos = 0;
    }
    void pop() { pos++; }
};

template <class Cap>
struct mf_graph {
   public:
    mf_graph() : _n(0) {}
    mf_graph(int n) : _n(n), g(n) {}

    int add_edge(int from, int to, Cap cap) {
        int m = int(pos.size());
        pos.push_back({from, int(g[from].size())});
        g[from].push_back(_edge{to, int(g[to].size()), cap});
        g[to].push_back(_edge{from, int(g[from].size()) - 1, 0});
        return m;
    }

    struct edge {
        int from, to;
        Cap cap, flow;
    };

    edge get_edge(int i) {
        int m = int(pos.size());
        auto& [f, s] = pos[i];
        auto _e = g[f][s];
        auto _re = g[_e.to][_e.rev];
        return edge{f, _e.to, _e.cap + _re.cap, _re.cap};
    }

    std::vector<edge> edges() {
        int m = int(pos.size());
        std::vector<edge> result;
        for (int i = 0; i < m; i++) {
            result.push_back(get_edge(i));
        }
        return result;
    }

    void change_edge(int i, Cap new_cap, Cap new_flow) {
        int m = int(pos.size());
        auto& _e = g[pos[i].first][pos[i].second];
        auto& _re = g[_e.to][_e.rev];
        _e.cap = new_cap - new_flow;
        _re.cap = new_flow;
    }

    Cap flow(int s, int t) {
        return flow(s, t, std::numeric_limits<Cap>::max());
    }
    Cap flow(int s, int t, Cap flow_limit) {
        std::vector<int> level(_n), iter(_n);
        simple_queue<int> que;

        auto bfs = [&]() {
            std::fill(level.begin(), level.end(), -1);
            level[s] = 0;
            que.clear();
            que.push(s);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (auto& e : g[v]) {
                    if (e.cap == 0 || level[e.to] >= 0) continue;
                    level[e.to] = level[v] + 1;
                    if (e.to == t) return;
                    que.push(e.to);
                }
            }
        };
        auto dfs = [&](const auto& self, int v, Cap up) {
            if (v == s) return up;
            Cap res = 0;
            int level_v = level[v];
            for (int& i = iter[v]; i < int(g[v].size()); i++) {
                _edge& e = g[v][i];
                if (level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;
                Cap d =
                    self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));
                if (d <= 0) continue;
                g[v][i].cap += d;
                g[e.to][e.rev].cap -= d;
                res += d;
                if (res == up) break;
            }
            return res;
        };

        Cap flow = 0;
        while (flow < flow_limit) {
            bfs();
            if (level[t] == -1) break;
            std::fill(iter.begin(), iter.end(), 0);
            while (flow < flow_limit) {
                Cap f = dfs(dfs, t, flow_limit - flow);
                if (!f) break;
                flow += f;
            }
        }
        return flow;
    }

    std::vector<bool> min_cut(int s) {
        std::vector<bool> visited(_n);
        simple_queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            visited[p] = true;
            for (auto e : g[p])
                if (e.cap && !visited[e.to]) {
                    visited[e.to] = true;
                    que.push(e.to);
                }
        }
        return visited;
    }

   private:
    int _n;
    struct _edge {
        int to, rev;
        Cap cap;
    };
    std::vector<std::pair<int, int>> pos;
    std::vector<std::vector<_edge>> g;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        // assignment problem - can be reduced to min cost flow
        int n, m;
        cin >> n >> m;
        // consider the network in the proof of menger's theorem
        mf_graph<int> g(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            g.add_edge(u - 1, v - 1, 1);
        }
        auto flow = g.flow(0, n - 1);
        cout << flow << '\n';
        vector<vector<int>> G(n);
        auto edges = g.edges();
        for (int i = 0; i < flow; ++i) {
            auto it = remove_if(begin(edges), end(edges),
                                [](const auto& x) { return x.flow == 0; });
            edges.erase(it, end(edges));
            for (auto& x : G) x.clear();
            for (int i = 0; i < (int)edges.size(); ++i) {
                auto edge = edges[i];
                G[edge.from].push_back(i);
            }
            queue<int> q;
            q.push(0);
            vector<int> d(n, -1), p(n, -1);
            d[0] = 0;
            while (!q.empty()) {
                auto u = q.front();
                q.pop();
                for (auto edge_id : G[u]) {
                    int v = edges[edge_id].to;
                    if (d[v] == -1) {
                        d[v] = d[u] + 1;
                        p[v] = edge_id;
                        q.push(v);
                    }
                }
            }
            int v = n - 1;
            vector<int> path;
            while (p[v] != -1) {
                path.push_back(p[v]);
                edges[p[v]].flow = 0;
                v = edges[p[v]].from;
            }
            reverse(begin(path), end(path));
            vector<int> vertices{edges[path[0]].from};
            for (auto id : path) vertices.push_back(edges[id].to);
            cout << vertices.size() << '\n';
            for (auto v : vertices) cout << v + 1 << ' ';
            cout << '\n';
        }
    }
}
