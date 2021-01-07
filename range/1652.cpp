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

void solve() {
    int n, q;
    cin >> n >> q;
    vector<string> a(n);
    rep(i, n) cin >> a[i];
    vvi pre(n + 1, vi(n + 1));
    rep(i, n) {
        pre[i][0] = 0;
        pre[0][i] = 0;
    }
    vi pre2(n + 1);
    rep(i, n) {
        rep(j, n) pre2[j + 1] += (a[i][j] == '*');
        rep(j, n) { pre[i + 1][j + 1] = pre[i + 1][j] + pre2[j + 1]; }
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        int z, w;
        cin >> z >> w;
        int ans = pre[z][w] - pre[z][y - 1] - pre[x - 1][w] + pre[x - 1][y - 1];
        cout << ans << "\n";
        ;
    }
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
