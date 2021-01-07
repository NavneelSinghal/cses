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

const Int mod = 1e9 + 7;
const int maxn = 1e6 + 5;
const int maxa = 1e6 + 5;
const int logmax = 25;

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

template <typename T>
T power(T a, int n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}

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

vector<mint> fact(maxn);

void precompute_facts() {
    fact[0] = 1;
    for (int i = 0; i < maxn - 1; i++) {
        fact[i + 1] = fact[i] * (i + 1);
    }
}

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

void solve() {
    int n;
    cin >> n;
    precompute_facts();
    mint factor(0);
    mint parity(1);
    for (int i = 0; i <= n; i++) {
        factor += parity / fact[i];
        parity *= -1;
    }
    mint ans = factor * fact[n];
    cout << ans << endl;
}

signed main() {
    fastio;
    cout << setprecision(20) << fixed;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
