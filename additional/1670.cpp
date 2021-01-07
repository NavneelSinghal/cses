#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
//#include <ext/rope>

using namespace __gnu_pbds;
// using namespace __gnu_cxx;
using namespace std;

#define int long long
#define double long double
#define Int signed
#define vi vector<int>
#define vI vector<Int>
#define vvi vector<vi>
#define vvI vector<vI>
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
#define rep4(i, a, b, c) for (int i = a; i < b; i += c)

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
const int LINF = INF * INF;
const double EPS = 1e-9;
const double PI = acosl(-1);

template <class T, class F = multiplies<T>>
T pwr(T a, long long n, F op = multiplies<T>(), T e = {1}) {
    assert(n >= 0);
    T res = e;
    while (n) {
        if (n & 1) res = op(res, a);
        if (n >>= 1) a = op(a, a);
    }
    return res;
}

template <unsigned Mod = 998244353>
struct Modular {
    using M = Modular;
    unsigned v;
    Modular(long long a = 0) : v((a %= Mod) < 0 ? a + Mod : a) {}
    M operator-() const { return M() -= *this; }
    M& operator+=(M r) {
        if ((v += r.v) >= Mod) v -= Mod;
        return *this;
    }
    M& operator-=(M r) {
        if ((v += Mod - r.v) >= Mod) v -= Mod;
        return *this;
    }
    M& operator*=(M r) {
        v = (uint64_t)v * r.v % Mod;
        return *this;
    }
    M& operator/=(M r) { return *this *= pwr(r, Mod - 2); }
    friend M operator+(M l, M r) { return l += r; }
    friend M operator-(M l, M r) { return l -= r; }
    friend M operator*(M l, M r) { return l *= r; }
    friend M operator/(M l, M r) { return l /= r; }
    friend bool operator==(M l, M r) { return l.v == r.v; }
    friend bool operator!=(M l, M r) { return l.v != r.v; }
    friend ostream& operator<<(ostream& os, M& a) { return os << a.v; }
    friend istream& operator>>(istream& is, M& a) {
        int64_t w;
        is >> w;
        a = M(w);
        return is;
    }
};

const int mod = 1e9 + 7;

using mint = Modular<mod>;

const int maxn = 5e5 + 5;
const int maxa = 1e6 + 5;
const int logmax = 25;

namespace IO {
const int BUFFER_SIZE = 1 << 15;
char input_buffer[BUFFER_SIZE];
int input_pos = 0, input_len = 0;
char output_buffer[BUFFER_SIZE];
int output_pos = 0;
char number_buffer[100];
uint8_t lookup[100];
void _update_input_buffer() {
    input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
    input_pos = 0;
    if (input_len == 0) input_buffer[0] = EOF;
}

inline char next_char(bool advance = true) {
    if (input_pos >= input_len) _update_input_buffer();

    return input_buffer[advance ? input_pos++ : input_pos];
}

template <typename T>
inline void read_int(T& number) {
    bool negative = false;
    number = 0;

    while (!isdigit(next_char(false)))
        if (next_char() == '-') negative = true;

    do {
        number = 10 * number + (next_char() - '0');
    } while (isdigit(next_char(false)));

    if (negative) number = -number;
}

template <typename T, typename... Args>
inline void read_int(T& number, Args&... args) {
    read_int(number);
    read_int(args...);
}

void _flush_output() {
    fwrite(output_buffer, sizeof(char), output_pos, stdout);
    output_pos = 0;
}

inline void write_char(char c) {
    if (output_pos == BUFFER_SIZE) _flush_output();

    output_buffer[output_pos++] = c;
}

template <typename T>
inline void write_int(T number, char after = '\0') {
    if (number < 0) {
        write_char('-');
        number = -number;
    }
    int length = 0;
    while (number >= 10) {
        uint8_t lookup_value = lookup[number % 100];
        number /= 100;
        number_buffer[length++] = (lookup_value & 15) + '0';
        number_buffer[length++] = (lookup_value >> 4) + '0';
    }
    if (number != 0 || length == 0) write_char(number + '0');
    for (int i = length - 1; i >= 0; i--) write_char(number_buffer[i]);
    if (after) write_char(after);
}

void IOinit() {
    // Make sure _flush_output() is called at the end of the program.
    bool exit_success = atexit(_flush_output) == 0;
    assert(exit_success);
    for (int i = 0; i < 100; i++) lookup[i] = (i / 10 << 4) + i % 10;
}
}  // namespace IO

using namespace IO;

#if 0
void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}
#endif

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
    size_t operator()(pair<int, int> x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(FIXED_RANDOM + 31 * x.first + x.second);
    }
};

int pows[20];

struct grid {
    int x[10];
    grid() {}
    grid(vector<int> a) {
        for (int i = 1; i < 10; ++i) {
            x[i] = a[i - 1];
        }
    }
    bool operator==(grid a) const {
        for (int i = 1; i < 10; ++i) {
            if (x[i] != a.x[i]) return false;
        }
        return true;
    }
    int hash() {
        int s = 0;
        for (int i = 1; i < 10; i++) {
            s += pows[i] * x[i];
        }
        return s;
    }
};

int dx[] = {1, 2, 1, 4, 7, 8, 6, 3, 8, 5, 4, 5};
int dy[] = {2, 3, 4, 7, 8, 9, 9, 6, 5, 6, 5, 2};

void solve(int case_no) {
    int x;
    vector<int> c;
    for (int i = 0; i < 9; ++i) {
        cin >> x;
        c.pb(x);
    }
    pows[0] = 1;
    for (int i = 1; i < 20; ++i) {
        pows[i] = pows[i - 1] * 10;
    }
    unordered_map<int, int, custom_hash> distance;
    queue<grid> q;
    grid cur(c);
    grid dest({1, 2, 3, 4, 5, 6, 7, 8, 9});
    q.push(cur);
    distance[cur.hash()] = 1;
    if (cur == dest) {
        cout << 0 << "\n";
        return;
    }
    grid g;
    while (!q.empty()) {
        g = q.front();
        q.pop();
        int gh = g.hash();
        for (int i = 0; i < 12; i++) {
            grid gg = g;
            swap(gg.x[dx[i]], gg.x[dy[i]]);
            int ggh = gg.hash();
            if (distance[ggh]) continue;
            if (gg == dest) {
                cout << distance[gh] << "\n";
            }
            distance[ggh] = distance[gh] + 1;
            q.push(gg);
        }
    }
}

signed main() {
    // IOinit();
    fastio;
    // cout << setprecision(10) << fixed;
    int t = 1;
    // read_int(t);
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
    }
    return 0;
}
