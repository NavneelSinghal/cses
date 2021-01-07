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

// order_of_key(k) - number of elements e such that func(e, k) returns true,
// where func is less or less_equal find_by_order(k) - kth element in the set
// counting from 0

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

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    vi v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int k = b - a + 1;
    vi pre(n + 1);
    rep(i, n) pre[i + 1] = pre[i] + v[i];
    vi mn(n + 1);
    rep(i, k) if (i) mn[i] = min(mn[i - 1], pre[i]);
    deque<int> q;
    rep(i, k) {
        while (!q.empty() && pre[i] <= pre[q.back()]) q.pop_back();
        q.pb(i);
    }
    for (int i = k; i < n + 1; i++) {
        mn[i - 1] = pre[q.front()];
        while (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && pre[i] <= pre[q.back()]) q.pop_back();
        q.pb(i);
    }
    mn[n] = pre[q.front()];
    int ans = -INF * INF;
    for (int x = a; x < n + 1; x++) {
        ans = max(ans, pre[x] - mn[x - a]);
    }
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
