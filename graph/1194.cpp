#include <bits/stdc++.h>
using namespace std;
 
using P = pair<int, int>;
template <class T>
using V = vector<T>;
 
template <class T>
struct simple_queue {
    std::vector<T> payload;
    int pos = 0;
    void reserve(int n) { payload.reserve(n); }
    int size() const { return int(payload.size()) - pos; }
    bool empty() const { return pos == int(payload.size()); }
    void push(const T& t) { payload.push_back(t); }
    template <typename... Args>
    T& emplace(Args&&... args) {
        return payload.emplace_back(args...);
    }
    T& front() { return payload[pos]; }
    void clear() { payload.clear(), pos = 0; }
    void pop() { pos++; }
};
 
template <class T>
struct simple_stack {
    std::vector<T> payload;
    void reserve(int n) { payload.reserve(n); }
    int size() const { return int(payload.size()); }
    bool empty() const { return payload.empty(); }
    void push(const T& t) { payload.push_back(t); }
    T& top() { return payload.back(); }
    void clear() { payload.clear(); }
    void pop() { payload.pop_back(); }
};
 
constexpr int inf = 1e9;
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    while (t--) {
        int n, m;
        cin >> n >> m;
        V<string> a(n);
        for (auto& x : a) cin >> x;
        V<P> dirs{pair{0, 1}, pair{1, 0}, pair{-1, 0}, pair{0, -1}};
        int x = -1, y = -1;
        simple_queue<P> q;
        V<V<int>> dist(n, vector<int>(m, inf));
        V<V<V<P>>> g(n, V<V<P>>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] == 'M') {
                    dist[i][j] = 0;
                    q.emplace(i, j);
                } else if (a[i][j] == 'A')
                    x = i, y = j;
                if (a[i][j] != '#') {
                    for (auto [dx, dy] : dirs) {
                        int ni = i + dx;
                        int nj = j + dy;
                        if (0 <= ni && ni < n && 0 <= nj && nj < m &&
                            a[ni][nj] != '#') {
                            g[i][j].emplace_back(ni, nj);
                        }
                    }
                }
            }
        }
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto [i, j] : g[x][y]) {
                if (dist[i][j] > dist[x][y] + 1) {
                    q.emplace(i, j);
                    dist[i][j] = dist[x][y] + 1;
                }
            }
        }
        V<V<int>> dist_me(n, V<int>(m, inf));
        V<V<P>> parent(n, V<P>(m, {-1, -1}));
        q.emplace(x, y);
        dist_me[x][y] = 0;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto [i, j] : g[x][y]) {
                if (dist_me[i][j] > dist_me[x][y] + 1 &&
                    dist_me[x][y] + 1 < dist[i][j]) {
                    q.emplace(i, j);
                    dist_me[i][j] = dist_me[x][y] + 1;
                    parent[i][j] = {x, y};
                }
            }
        }
        int bx = -1, by = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (dist_me[i][j] != inf &&
                    (i == 0 || j == 0 || i == n - 1 || j == m - 1)) {
                    bx = i, by = j;
                    break;
                }
            }
        }
        if (bx == -1) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            V<P> path;
            while (bx != -1) {
                path.emplace_back(bx, by);
                tie(bx, by) = parent[bx][by];
            }
            cout << path.size() - 1 << '\n';
            reverse(begin(path), end(path));
            auto dir = [](const P& b, const P& a) {
                if (a.first == b.first) {
                    if (a.second == b.second + 1) {
                        return 'R';
                    } else {
                        return 'L';
                    }
                } else if (a.first == b.first + 1) {
                    return 'D';
                } else {
                    return 'U';
                }
            };
            for (int i = 1; i < (int)path.size(); ++i)
                cout << dir(path[i - 1], path[i]);
            cout << '\n';
        }
    }
}
