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

#define int long long
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

const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;
const int logmax = 25;

int powmod(int a, int n) {
    int ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

int inv(int a) { return powmod(a, mod - 2); }

int t[4 * maxn];

void build(vi &a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
        return;
    }
    int tm = (tl + tr) / 2;
    build(a, v * 2, tl, tm);
    build(a, v * 2 + 1, tm + 1, tr);
    t[v] = max(t[2 * v], t[2 * v + 1]);
}

void update(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        t[v] = val;
        return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        update(v * 2, tl, tm, pos, val);
    else
        update(v * 2 + 1, tm + 1, tr, pos, val);
    t[v] = max(t[2 * v], t[2 * v + 1]);
}

int query(int v, int tl, int tr, int l, int r) {
    if (l > r) return -1;
    if (l == tl && r == tr) return t[v];
    int tm = (tl + tr) / 2;
    return max(query(v * 2, tl, tm, l, min(r, tm)),
               query(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r));
}

void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n);
    rep(i, n) cin >> a[i];
    build(a, 1, 0, n - 1);
    rep(i, m) {
        int x;
        cin >> x;
        int left = 0;
        int right = n - 1;
        int ans = -1;
        int tot = -1;
        while (left <= right) {
            int mid = (left + right) / 2;
            int poss = query(1, 0, n - 1, 0, mid);
            if (poss >= x) {
                ans = mid;
                tot = poss;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (ans == -1)
            cout << "0 ";
        else {
            cout << ans + 1 << " ";
            update(1, 0, n - 1, ans, tot - x);
        }
    }
    cout << endl;
    ;
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
