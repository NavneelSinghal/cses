#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;

#define int long long
#define double long double
#define Int signed
#define vi vector<int>
#define vvi vector<vi>
#define vd vector<double>
#define vvd vector<vd>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define mii map<int, int>
#define unordered_map gp_hash_table

#define OVERLOADED_MACRO(M, ...) _OVR(M, _COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)
#define _OVR(macroName, number_of_args) _OVR_EXPAND(macroName, number_of_args)
#define _OVR_EXPAND(macroName, number_of_args) macroName##number_of_args

#define _COUNT_ARGS(...) \
    _ARG_PATTERN_MATCH(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define _ARG_PATTERN_MATCH(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N

#define rep(...) OVERLOADED_MACRO(rep, __VA_ARGS__)
#define repd(...) OVERLOADED_MACRO(repd, __VA_ARGS__)

#define rep3(i, a, b) for (int i = a; i < b; ++i)
#define rep2(i, n) rep3(i, 0, n)
#define repd3(i, a, b) for (int i = b - 1; i >= a; --i)
#define repd2(i, n) repd3(i, 0, n)

#define F first
#define S second

#define fastio                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(v) v.begin(), v.end()

#define bitcount __builtin_popcountll
#define gcd __gcd
// for trailing 1s, do trailing0(n + 1)
#define leading0 __builtin_clzll
#define trailing0 __builtin_ctzll
#define isodd(n) (n & 1)
#define iseven(n) (!(n & 1))

#define sz(v) ((int)v.size())
#define del_rep(v) \
    sort(all(v));  \
    v.erase(unique(all(v)), v.end());
#define checkbit(n, b) ((n >> b) & 1)

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
void err(std::istream_iterator<std::string> it) {}
template <typename T, typename... Args>
void err(std::istream_iterator<std::string> it, T a, Args... args) {
    std::cerr << *it << " = " << a << std::endl;
    err(++it, args...);
}
template <typename T1, typename T2>
inline std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    print_container(v);
}
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::set<T>& v) {
    print_container(v);
}
template <typename T1, typename T2>
inline std::ostream& operator<<(std::ostream& os, const std::map<T1, T2>& v) {
    print_container(v);
}
template <typename T1, typename T2, class C>
inline std::ostream& operator<<(std::ostream& os,
                                const unordered_map<T1, T2, C>& v) {
    print_container(v);
}
template <typename T, class C>
inline std::ostream& operator<<(std::ostream& os,
                                const unordered_set<T, C>& v) {
    print_container(v);
}
template <typename T1, typename T2>
inline std::ostream& operator<<(std::ostream& os,
                                const std::multimap<T1, T2>& v) {
    print_container(v);
}
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::multiset<T>& v) {
    print_container(v);
}
#else
#define debug(args...) 0
#endif

// order_of_key(k) - number of elements e such that func(e, k) returns true,
// where func is less or less_equal find_by_order(k) - kth element in the set
// counting from 0
//
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_multiset;

const int INF = 1e9;
const double EPS = 1e-9;
const double PI = acosl(-1);
const int mod = 1e9 + 7;
const int maxn = 5e5 + 5;
const int maxa = 1e6 + 5;
const int logmax = 25;

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

template <int MOD = 998'244'353>
struct Modular {
    int value;
    static const int MOD_value = MOD;

    Modular(long long v = 0) {
        value = v % MOD;
        if (value < 0) value += MOD;
    }
    Modular(long long a, long long b) : value(0) {
        *this += a;
        *this /= b;
    }

    Modular& operator+=(Modular const& b) {
        value += b.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }
    Modular& operator-=(Modular const& b) {
        value -= b.value;
        if (value < 0) value += MOD;
        return *this;
    }
    Modular& operator*=(Modular const& b) {
        value = (long long)value * b.value % MOD;
        return *this;
    }

    friend Modular mexp(Modular a, long long e) {
        Modular res = 1;
        while (e) {
            if (e & 1) res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }
    friend Modular inverse(Modular a) { return mexp(a, MOD - 2); }

    Modular& operator/=(Modular const& b) { return *this *= inverse(b); }
    friend Modular operator+(Modular a, Modular const b) { return a += b; }
    friend Modular operator-(Modular a, Modular const b) { return a -= b; }
    friend Modular operator-(Modular const a) { return 0 - a; }
    friend Modular operator*(Modular a, Modular const b) { return a *= b; }
    friend Modular operator/(Modular a, Modular const b) { return a /= b; }
    friend std::ostream& operator<<(std::ostream& os, Modular const& a) {
        return os << a.value;
    }
    friend bool operator==(Modular const& a, Modular const& b) {
        return a.value == b.value;
    }
    friend bool operator!=(Modular const& a, Modular const& b) {
        return a.value != b.value;
    }
};

template <typename T>
struct Matrix {
    signed rows, cols;
    vector<vector<T>> mat;
    Matrix(int r, int c)
        : rows(r), cols(c), mat(vector<vector<T>>(r, vector<T>(c))){};
    void fill(T val) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = val;
            }
        }
    }
    void reset() { fill(0); }
    void setid() {
        assert(rows == cols);
        for (int i = 0; i < rows; i++) {
            mat[i][i] = 1;
        }
    }
    static Matrix id(int n) {
        Matrix m(n, n);
        m.setid();
        return m;
    }
    Matrix operator+(const Matrix& a) const {
        assert(rows == a.rows && cols == a.cols);
        Matrix<T> res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.mat[i][j] = mat[i][j] + a.mat[i][j];
            }
        }
    }
    Matrix<T> operator*(const Matrix<T>& a) const {
        assert(cols == a.rows);
        Matrix<T> res(rows, a.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < a.cols; j++) {
                res.mat[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    res.mat[i][j] += mat[i][k] * a.mat[k][j];
                }
            }
        }
        return res;
    }
    void operator+=(const Matrix& a) { *this = *this + a; }
    void operator*=(const Matrix& a) { *this = *this * a; }
};

template <typename T>
T power(T a, int n = 1, T id = 1) {
    T ans = id;
    while (n) {
        if (n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}

using mint = Modular<mod>;

void solve() {
    int n, m;
    cin >> n >> m;
    vvpii g(n);
    rep(i, m) {
        int u, v, c;
        cin >> u >> v >> c;
        --u, --v;
        g[u].eb(v, c);
    }
    vi dist(n, INF * INF), par(n, -1);
    int s = 0;
    dist[s] = 0;
    priority_queue<pii, vpii, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().S;
        int dv = q.top().F;
        q.pop();
        if (dv != dist[v]) continue;
        for (auto edge : g[v]) {
            int to = edge.F;
            int len = edge.S;
            if (dist[v] + len < dist[to]) {
                dist[to] = dist[v] + len;
                par[to] = v;
                q.push({dist[to], to});
            }
        }
    }
    for (auto d : dist) {
        cout << d << " ";
    }
    cout << endl;
}

signed main() {
    fastio;
    cout << setprecision(6) << fixed;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
