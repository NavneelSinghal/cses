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

template <bool ToShuffle = false>
struct bipartite_matching_hopcroft_karp {
   public:
    bipartite_matching_hopcroft_karp(int _n_left, int _n_right)
        : n_left(_n_left),
          n_right(_n_right),
          g(_n_left),
          match_from_left(_n_left, -1),
          match_from_right(_n_right, -1),
          dist(_n_left) {}

    void add(int u, int v) { g[u].push_back(v); }

    void reset() { matchings = 0, computed = false; }

    int get_max_matching() {
        if (!computed) compute_max_matching();
        return matchings;
    }

    std::pair<std::vector<int>, std::vector<int>> minimum_vertex_cover() {
        if (!computed) compute_max_matching();
        std::vector<int> L, R;
        for (int u = 0; u < n_left; ++u) {
            if (!~dist[u])
                L.push_back(u);
            else if (~match_from_left[u])
                R.push_back(match_from_left[u]);
        }
        return {L, R};
    }

    std::vector<std::pair<int, int>> get_edges() {
        if (!computed) compute_max_matching();
        std::vector<std::pair<int, int>> ans;
        for (int u = 0; u < n_left; ++u)
            if (~match_from_left[u]) ans.emplace_back(u, match_from_left[u]);
        return ans;
    }

   private:
    template <class T>
    struct simple_queue {
        std::vector<T> payload;
        int pos = 0;
        void reserve(int n) { payload.reserve(n); }
        int size() const { return int(payload.size()) - pos; }
        bool empty() const { return pos == int(payload.size()); }
        void push(const T& t) { payload.push_back(t); }
        T& front() { return payload[pos]; }
        void clear() { payload.clear(), pos = 0; }
        void pop() { pos++; }
    };

    int n_left, n_right, matchings = 0;
    bool computed = false;
    std::vector<std::basic_string<int>> g;
    std::vector<int> match_from_left, match_from_right;
    std::vector<int> dist;

    void bfs() {
        simple_queue<int> q;
        for (int u = 0; u < n_left; ++u) {
            if (!~match_from_left[u])
                q.push(u), dist[u] = 0;
            else
                dist[u] = -1;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u]) {
                int U = match_from_right[v];
                if (~U && !~dist[U]) {
                    dist[U] = dist[u] + 1;
                    q.push(U);
                }
            }
        }
    }

    bool dfs(int u) {
        for (auto v : g[u])
            if (!~match_from_right[v]) {
                match_from_left[u] = v, match_from_right[v] = u;
                return true;
            }
        for (auto v : g[u])
            if (dist[match_from_right[v]] == dist[u] + 1 &&
                dfs(match_from_right[v])) {
                match_from_left[u] = v, match_from_right[v] = u;
                return true;
            }
        return false;
    }

    void compute_max_matching() {
        while (true) {
            bfs();
            int new_matchings = 0;
            for (int u = 0; u < n_left; ++u)
                if (!~match_from_left[u] && dfs(u)) ++new_matchings;
            if (!new_matchings) break;
            matchings += new_matchings;
        }
        computed = true;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        bipartite_matching_hopcroft_karp g(n, n);
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < n; ++j) {
                if (s[j] == 'o') {
                    g.add(i, j);
                }
            }
        }
        auto [l, r] = g.minimum_vertex_cover();
        cout << l.size() + r.size() << '\n';
        for (auto x : l) cout << 1 << ' ' << x + 1 << '\n';
        for (auto x : r) cout << 2 << ' ' << x + 1 << '\n';
    }
}

