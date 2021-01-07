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
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;

#define FLSH fflush(stdout)
#define fileIO(name)                 \
    freopen(name ".in", "r", stdin); \
    freopen(name ".out", "w", stdout);
#define PRECISION(x) cout << fixed << setprecision(x);
#define FAST_IO              \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set;

typedef long long ll;
typedef long double LD;
#define int ll
#define double LD
#define pb push_back
#define mp make_pair
#define REP(i, n) for (int i = 0; i < n; i++)
#define REP1(i, n) for (int i = 1; i <= n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define REPD(i, n) for (int i = n - 1; i >= 0; i--)
#define REPD1(i, n) for (int i = n; i > 0; i--)
#define FORD(i, a, b) for (int i = a; i >= b; i--)
#define foreach(c, itr) \
    for (__typeof((c).begin()) itr = (c).begin(); itr != (c).end(); itr++)
#define remax(a, b) a = max(a, b)
#define remin(a, b) a = min(a, b)
#define all(v) v.begin(), v.end()
typedef map<int, int> mii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
#define F first
#define S second
#define PQ(type) priority_queue<type>
#define PQD(type) priority_queue<type, vector<type>, greater<type> >
#define ITR ::iterator it
#define WL(t) while (t--)
#define sz(x) ((int)(x).size())
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define TR(container, it)                                  \
    for (typeof(container.begin()) it = container.begin(); \
         it != container.end(); it++)
#define sqr(x) ((x) * (x))

const int MAXN = 100005;
const int SQRTN = 1003;
const int LOGN = 22;
const double PI = acos(-1);
const int INF = 1000000000;
const int MOD = 1000000007;
const int FMOD = 998244353;
const double eps = 1e-9;

mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
#define SHUF(v) shuffle(all(v), RNG);

template <typename T>
T gcd(T a, T b) {
    return (b ? __gcd(a, b) : a);
}
template <typename T>
T lcm(T a, T b) {
    return (a * (b / gcd(a, b)));
}
int add(int a, int b, int c) {
    int res = a + b;
    return (res >= c ? res - c : res);
}
int mod_neg(int a, int b, int c) {
    int res;
    if (abs(a - b) < c)
        res = a - b;
    else
        res = (a - b) % c;
    return (res < 0 ? res + c : res);
}
int mul(int a, int b, int c) {
    ll res = (ll)a * b;
    return (res >= c ? res % c : res);
}
ll mulmod(ll a, ll b, ll m) {
    ll q = (ll)(((LD)a * (LD)b) / (LD)m);
    ll r = a * b - q * m;
    if (r > m) r %= m;
    if (r < 0) r += m;
    return r;
}
template <typename T>
T expo(T e, T n) {
    T x = 1, p = e;
    while (n) {
        if (n & 1) x = x * p;
        p = p * p;
        n >>= 1;
    }
    return x;
}
template <typename T>
T power(T e, T n, T m) {
    T x = 1, p = e;
    while (n) {
        if (n & 1) x = mul(x, p, m);
        p = mul(p, p, m);
        n >>= 1;
    }
    return x;
}
template <typename T>
T extended_euclid(T a, T b, T &x, T &y) {
    T xx = 0, yy = 1;
    y = 0;
    x = 1;
    while (b) {
        T q = a / b, t = b;
        b = a % b;
        a = t;
        t = xx;
        xx = x - q * xx;
        x = t;
        t = yy;
        yy = y - q * yy;
        y = t;
    }
    return a;
}
template <typename T>
T mod_inverse(T a, T n) {
    T x, y, z = 0;
    T d = extended_euclid(a, n, x, y);
    return (d > 1 ? -1 : mod_neg(x, z, n));
}

using namespace std;

signed main() {
    FAST_IO
    PRECISION(10)

    int n;
    cin >> n;
    vi a(n);
    int x;
    mii m;
    REP(i, n) {
        cin >> x;
        m[x] = 1;
    }
    int ans = 0;
    for (auto w : m) {
        ans++;
    }
    cout << ans << endl;

    return 0;
}
