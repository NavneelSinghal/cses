// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx")
// #pragma GCC optimize("unroll-loops")

#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
//#include <ext/rope>

using namespace __gnu_pbds;
// using namespace __gnu_cxx;
using namespace std;

using ll = long long;

// #define int long long
#define unordered_map gp_hash_table
#define cauto const auto

template <typename T>
void ignore_unused(const T &) {}
#ifdef DEBUG
#define debug(args...)                               \
    {                                                \
        std::string _s = #args;                      \
        replace(_s.begin(), _s.end(), ',', ' ');     \
        std::stringstream _ss(_s);                   \
        std::istream_iterator<std::string> _it(_ss); \
        err(_it, args);                              \
    }
#define print_container(v)          \
    {                               \
        bool first = true;          \
        os << "[";                  \
        for (auto x : v) {          \
            if (!first) os << ", "; \
            os << x;                \
            first = false;          \
        }                           \
        return os << "]";           \
    }
void err(std::istream_iterator<std::string> it) { ignore_unused(it); }
template <typename T, typename... Args>
void err(std::istream_iterator<std::string> it, T a, Args... args) {
    std::cerr << *it << " = " << a << std::endl;
    err(++it, args...);
}

// clang-format off
 
template <typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) { return os << "(" << p.first << ", " << p.second << ")"; }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::vector<T>& v) { print_container(v); }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::set<T>& v) { print_container(v); }
template <typename T1, typename T2> inline std::ostream &operator << (std::ostream & os, const std::map<T1, T2>& v) { print_container(v); }
template <typename T1, typename T2, class C> inline std::ostream &operator << (std::ostream & os, const unordered_map<T1, T2, C>& v) { print_container(v); }
template <typename T, class C> inline std::ostream &operator << (std::ostream & os, const unordered_set<T, C>& v) { print_container(v); }
template <typename T1, typename T2> inline std::ostream &operator << (std::ostream & os, const std::multimap<T1, T2>& v) { print_container(v); }
template <typename T> inline std::ostream &operator << (std::ostream & os, const std::multiset<T>& v) { print_container(v); }
#else
#define debug(args...) 0
#endif
 
template <typename X, typename Y> X &remin(X &x, const Y &y) { return x = (y < x) ? y : x; }
template <typename X, typename Y> X &remax(X &x, const Y &y) { return x = (x < y) ? y : x; }
template <typename X, typename Y> [[nodiscard]] bool ckmin(X &x, const Y &y) { return (y < x) ? (x = y, 1) : 0; }
template <typename X, typename Y> [[nodiscard]] bool ckmax(X &x, const Y &y) { return (x < y) ? (x = y, 1) : 0; }
template <typename T> inline T sq(T a) { return a * a; }
template <typename T> inline T sq_dist(pair<T, T> &a, pair<T, T> &b) { return sq(a.first - b.first) + sq(a.second - b.second); }
template <typename T> inline long double dist(pair<T, T> &a, pair<T, T> &b) { return sqrtl(sq_dist(a, b)); }
inline long long isqrt(long long n) {
    long long sq = (long long)sqrtl((long double)n) - 2;
    sq = max(sq, 0LL);
    while (sq * sq < n) sq++;
    if ((sq * sq) == n) return sq;
    return sq - 1;
}
inline bool is_sq(int n) { int w = (int)isqrt(n); return w * w == n; }
 
struct custom_hash {
    // http://xorshift.di.unimi.it/splitmix64.c
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
struct pair_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<int, int> p) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(p.first * 31 + p.second + FIXED_RANDOM);
    }
};
 
void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    ignore_unused(fin);
    ignore_unused(fout);
}

// clang-format on

// constexpr int mod = 998244353;
constexpr int mod = 1e9 + 7;
constexpr int64_t linf = 3e18;
constexpr long double pi = acosl(-1.0);
constexpr long double eps = 1e-9;

[[nodiscard]] int64_t pwr_mod(int64_t a, int64_t n, int mod = ::mod) {
    int64_t ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

// when using integers, keep overflow in mind
template <typename T>
T pwr(T a, int64_t n) {
    T ans(1);
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

void precompute() {}

struct graph_edge_pointers {
    struct edge {
        int to, nxt;  // to = other vertex,
                               // nxt = index of the prev edge from cur vertex
        edge(int to, int nxt) : to(to), nxt(nxt) {}
    };

    vector<int>
        head;  // head[i] = index of the last edge emanating from vertex i
    vector<edge> edges;
    // vector<int> siz;
    int cur_edges;

    graph_edge_pointers(int n, int m) {
        head.assign(n, -1);
        cur_edges = 0;
        edges.reserve(m);
        // siz.assign(n);
    }

    // while adding (u, v), (v, u), we have i, i^1 as corresponding edges
    void add_edge(int u, int v) {
        edges.emplace_back(v, head[u]);
        head[u] = cur_edges++;
    }
};

void solve(int) {
    int n, m;
    cin >> n >> m;

    graph_edge_pointers g(n, m * 2);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g.add_edge(u, v);
        g.add_edge(v, u);
    }

    vector<int> dir(m, -1);
    vector<int> vis(n);
    vector<int> in_parity(n);
    vector<int> depth(n);

    function<void(int, int)> dfs = [&](int u, int p) {
        vis[u] = 1;
        if (p == -1)
            depth[u] = 0;
        else
            depth[u] = depth[p] + 1;
        for (int i = g.head[u]; ~i; i = g.edges[i].nxt) {
            int v = g.edges[i].to;
            if (v == p) continue;
            // assign directions to back edges
            if (vis[v] && depth[v] < depth[u]) {
                if (i & 1)  // direction of back edge is opposite to what was
                            // given in the input
                    dir[i >> 1] = 1;
                else
                    dir[i >> 1] = 0;
                in_parity[v] ^= 1;  // back edges are directed away in their
                                    // natural orientation
                // out_parity[u] ^= 1;
            } else if (!vis[v]) {
                dfs(v, u);
            }
        }
    };

    function<void(int, int)> get_ans = [&](int u, int parent_edge_index) {
        for (int i = g.head[u]; ~i; i = g.edges[i].nxt) {
            // if either already assigned or this edge corresponds to the parent
            // edge's conjugate, this iteration is useless due to it being a
            // back edge or reverse forward edge
            if (i == (parent_edge_index ^ 1) || dir[i >> 1] != -1) continue;
            // otherwise, assign recursively
            get_ans(g.edges[i].to, i);
        }
        // if we are at root, can't adjust from parent
        if (parent_edge_index == -1) return;
        // if there is an even number of edges incoming into u
        // since in_parity[u] has been updated by stuff below it already
        // by orienting edges and stuff
        // we need to update parent using this (assignment to edges has been
        // completed for back edges, so only forward edges remain)
        // proof of why arbitrary assignments to back-edges work:
        // since the tree is a spanning tree, the sum of indegrees assigned
        // due to back edges is m_comp - n_comp + 1
        // now since it is connected, and there exists at least 1 unassigned
        // edge for each vertex (apart from the root), we can adjust and get
        // a unique assignment, where everything but the root has even indegree
        // since the root has degree dependent on the parity of m, any
        // arbitrary assignment to the back edges works, if there exists a sol
        // at all.
        if (!in_parity[u]) in_parity[g.edges[parent_edge_index ^ 1].to] ^= 1;
        dir[parent_edge_index >> 1] =
            in_parity[u] ^ (parent_edge_index & 1) ^ 1;
        in_parity[u] = 0; // after the above assignments, we can do this
    };

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            dfs(i, -1);
            get_ans(i, -1);
            if (in_parity[i] == 1) {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        int v = g.edges[i << 1].to + 1;
        int u = g.edges[(i << 1) | 1].to + 1;
        if (dir[i]) {
            cout << u << ' ' << v << '\n';
        } else {
            cout << v << ' ' << u << '\n';
        }
    }
}

void brute(int) {}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
        // brute(_t);
    }
    return 0;
}
