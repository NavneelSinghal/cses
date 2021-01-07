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
const int maxa = 1e6 + 5;
const int logmax = 25;

int powmod(int a, int n, int m = mod) {
    int ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % m;
        a = (a * a) % m;
        n >>= 1;
    }
    return ans;
}

int powe(int a, int n) {
    int ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}

int inv(int a) { return powmod(a, mod - 2); }

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
    int d = 2, big, small, ans = 0, nums, sum;
    do {
        big = n / (d - 1);
        small = n / d + 1;
        nums = big - small + 1;
        sum = big + small;
        if (nums % 2)
            sum /= 2;
        else
            nums /= 2;
        sum %= mod;
        nums %= mod;
        sum = sum * nums % mod;
        sum = sum * (d - 1) % mod;
        ans += sum;
        ans %= mod;
        d++;
    } while (small > d);
    for (int i = 1; i < small; i++) {
        ans += (n / i) * i;
        ans %= mod;
    }
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
