#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

// smaller names
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

#define rep(i, n) for (int i = 0; i < n; i++)
#define rep2(i, a, b) for (int i = a; i < b; i++)
#define repd2(i, a, b) for (int i = b - 1; i >= a; i--)
#define repd(i, n) for (int i = n - 1; i >= 0; i--)

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

const int INF = 1e9;
const double EPS = 1e-9;
const double PI = acosl(-1);

// order_of_key(k) - number of items smaller than k
// find_by_order(k) - kth element in the set counting from 0

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_multiset;

const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;
const int maxa = 1e6 + 5;
const int logmax = 25;

// fast exponentiation

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

#if 0
 
//modular int library
 
template <int MOD=998'244'353>
struct Modular {
    int value;
    static const int MOD_value = MOD;
 
    Modular(long long v = 0) { value = v % MOD; if (value < 0) value += MOD;}
    Modular(long long a, long long b) : value(0){ *this += a; *this /= b;}
 
    Modular& operator+=(Modular const& b) {value += b.value; if (value >= MOD) value -= MOD; return *this;}
    Modular& operator-=(Modular const& b) {value -= b.value; if (value < 0) value += MOD;return *this;}
    Modular& operator*=(Modular const& b) {value = (long long)value * b.value % MOD;return *this;}
 
    friend Modular mexp(Modular a, long long e) {
        Modular res = 1; while (e) { if (e&1) res *= a; a *= a; e >>= 1; }
        return res;
    }
    friend Modular inverse(Modular a) { return mexp(a, MOD - 2); }
 
    Modular& operator/=(Modular const& b) { return *this *= inverse(b); }
    friend Modular operator+(Modular a, Modular const b) { return a += b; }
    friend Modular operator-(Modular a, Modular const b) { return a -= b; }
    friend Modular operator-(Modular const a) { return 0 - a; }
    friend Modular operator*(Modular a, Modular const b) { return a *= b; }
    friend Modular operator/(Modular a, Modular const b) { return a /= b; }
    friend std::ostream& operator<<(std::ostream& os, Modular const& a) {return os << a.value;}
    friend bool operator==(Modular const& a, Modular const& b) {return a.value == b.value;}
    friend bool operator!=(Modular const& a, Modular const& b) {return a.value != b.value;}
};
 
using mint = Modular<mod>;

#endif

#if 0
 
//matrix library
 
template <typename T>
struct Matrix {
    signed rows, cols;
    vector<vector<T>> mat;
    Matrix (int r, int c) : rows(r), cols(c), mat (vector<vector<T>> (r, vector<T>(c))) {};
    void fill(T val) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = val;
            }
        }
    }
    void reset() {
        fill(0);
    }
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
    Matrix operator + (const Matrix& a) const {
        assert(rows == a.rows && cols == a.cols);
        Matrix<T> res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.mat[i][j] = mat[i][j] + a.mat[i][j];
            }
        }
    }
    Matrix<T> operator * (const Matrix<T>& a) const {
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
    void operator += (const Matrix& a) {
        *this = *this + a;
    }
    void operator *= (const Matrix& a) {
        *this = *this * a;
    }
};

#endif

#if 0
 
//smallest prime divisor computation
 
vi spf(maxa, -1);
 
void precompute(){
    spf[0] = spf[1] = 1;
    for(int i = 2; i < maxa; i++){
        if(spf[i] == -1){
            for(int j = i; j < maxa; j += i){
                if(spf[j] == -1) spf[j] = i;
            }
        }
    }
}

#endif

#if 0
 
//factorial precomputation
 
vector<mint> fact(maxn);
void precompute_facts(){
    fact[0] = 1;
    for(int i = 0; i < maxn - 1; i++){
        fact[i + 1] = fact[i] * (i + 1);
    }
}

#endif

#if 0
 
//O(1) square root
 
inline long long isqrt(long long n){
    double N = n;
    N = sqrtl(N);
    long long sq = N-2;
    sq = max(sq,0LL);
    while(sq*sq<n){
        sq++;
    }
    if((sq*sq)==n)
        return sq;
    return sq-1;
}

#endif

// custom hash function

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

// segment tree

#if 0
 
typedef struct {
    vi a;
} node;
 
node t[4*maxn];
 
node combine (node n1, node n2) {
    node ans;
    
    return ans;
}
 
node make_node (int val) {
    return {vi(val)};
}
 
const node ID = {vi()};
 
void build (int v, int l, int r, vi &a) {
    if (l == r) {
        t[v] = make_node(a[l]);
        return;
    }
    int mid = (l + r)/2;
    build (2*v, l, mid, a);
    build (2*v + 1, mid + 1, r, a);
    t[v] = combine(t[2*v], t[2*v + 1]);
    return;
}
 
void update (int v, int l, int r, int idx, int val) {
    if (l == r) {
        t[v] = make_node(val);
        return;
    }
    int mid = (l + r)/2;
    if (idx <= mid) update(2*v, l, mid, idx, val);
    else update(2*v + 1, mid + 1, r, idx, val);
    t[v] = combine(t[2*v], t[2*v + 1]);
}
 
node query (int v, int tl, int tr, int l, int r) {
    if (l > r) return ID;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return combine(query(2*v, tl, tm, l, min(r, tm)), query(2*v + 1, tm + 1, tr, max(l, tm + 1), r));
}

#endif

void solve() {
    int n, k;
    cin >> n >> k;
    vi a(n);
    rep(i, n) cin >> a[i];
    ordered_multiset s;
    rep(i, k - 1) s.insert(a[i]);
    for (int i = k - 1; i < n; i++) {
        s.insert(a[i]);
        cout << *s.find_by_order((k - 1) / 2) << " ";
        s.erase(s.find_by_order(s.order_of_key(a[i - k + 1])));
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
}
