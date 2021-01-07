#pragma GCC optimize("Ofast")

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <ext/pb_ds/assoc_container.hpp>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace __gnu_pbds;
using namespace std;

#define int long long
#define Int signed
#define double long double
#define vi vector<int>
#define vvi vector<vi>
#define vd vector<double>
#define vvd vector<vd>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define mii map<int, int>
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
#define INF 2e9
#define EPS 1e-9
#define PI acosl(-1)

const int mod = 1e9 + 7;
const int maxn = 1e6 + 5;
const int maxa = 1e6 + 5;
const int logmax = 25;

// modular int library

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

using mint = Modular<mod>;

// matrix library

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

// smallest prime divisor computation

vi spf(maxa, -1);

void precompute() {
    spf[0] = spf[1] = 1;
    for (int i = 2; i < maxa; i++) {
        if (spf[i] == -1) {
            for (int j = i; j < maxa; j += i) {
                if (spf[j] == -1) spf[j] = i;
            }
        }
    }
}

// factorial precomputation

vector<mint> fact(maxn);

void precompute_facts() {
    fact[0] = 1;
    for (int i = 0; i < maxn - 1; i++) {
        fact[i + 1] = fact[i] * (i + 1);
    }
}

// O(1) square root

inline long long isqrt(long long n) {
    double N = n;
    N = sqrtl(N);
    long long sq = N - 2;
    sq = max(sq, 0LL);
    while (sq * sq < n) {
        sq++;
    }
    if ((sq * sq) == n) return sq;
    return sq - 1;
}

const int mx = 7;
bool a[mx][mx];
int ans = 0;
string s;

void search(int i, int j, int steps = 0) {
    if (i == mx - 1 && j == 0) {
        if (steps == mx * mx - 1) {
            ans++;
        }
        return;
    }
    if (a[i][j]) return;
    // now note that if we are at a square on the edge, and we arrived there in
    // a direction perp to the edge, then if both the adjacent vertices are
    // unvisited, then we cant visit at least one of them, because the path
    // divides the board into two regions
    if ((j > 0 && j < mx - 1 && !a[i][j + 1] && !a[i][j - 1] &&
         (i == 0 || i == mx - 1)) ||
        (i > 0 && i < mx - 1 && !a[i + 1][j] && !a[i - 1][j] &&
         (j == 0 || j == mx - 1)))
        return;
    // also note that if the square is somewhere in the middle, and there the
    // other square in the same direction is visited, then the path forms a loop,
    // and divides the board into a certain number of parts, not both of which
    // can be filled completely, if we have both other neighbours in the other
    // direction unvisited
    if (i > 0 && j > 0 && i < 6 && j < 6) {
        if (a[i][j + 1] && a[i][j - 1] && !a[i + 1][j] && !a[i - 1][j]) return;
        if (!a[i][j + 1] && !a[i][j - 1] && a[i + 1][j] && a[i - 1][j]) return;
    }
    a[i][j] = true;
    char c = s[steps];
    if (c == '?') {
        if (i > 0 && !a[i - 1][j]) {
            search(i - 1, j, steps + 1);
        }
        if (i < mx - 1 && !a[i + 1][j]) {
            search(i + 1, j, steps + 1);
        }
        if (j > 0 && !a[i][j - 1]) {
            search(i, j - 1, steps + 1);
        }
        if (j < mx - 1 && !a[i][j + 1]) {
            search(i, j + 1, steps + 1);
        }
    } else if (c == 'U') {
        if (i > 0 && !a[i - 1][j]) {
            search(i - 1, j, steps + 1);
        }
    } else if (c == 'D') {
        if (i < mx - 1 && !a[i + 1][j]) {
            search(i + 1, j, steps + 1);
        }
    } else if (c == 'L') {
        if (j > 0 && !a[i][j - 1]) {
            search(i, j - 1, steps + 1);
        }
    } else if (c == 'R') {
        if (j < mx - 1 && !a[i][j + 1]) {
            search(i, j + 1, steps + 1);
        }
    }
    a[i][j] = false;
}

void solve() {
    cin >> s;
    // cin >> mx;
    rep(i, mx) rep(j, mx) a[i][j] = false;
    search(0, 0);
    cout << ans << endl;
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
