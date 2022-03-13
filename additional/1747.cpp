#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif
 
#include "bits/stdc++.h"
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif
 
using ll = int64_t;
using ull = uint64_t;
using ld = long double;
 
using namespace std;
 
// 0-based indexing for API
// 1-based indexing for internals
template <typename T>
struct Fenwick {
    int n;
    vector<T> t;
    Fenwick(int n) : n(n), t(n + 1) {}
    Fenwick(int n, T default_value) : n(n), t(n + 1, default_value) {
        for (int i = 1; i <= n; ++i) {
            int j = i + (i & (-i));
            if (j <= n) t[j] += t[i];
        }
    }
    // prefix sum [0, i)
    T query(int i) {
        T s = 0;
        while (i) {
            s += t[i];
            i -= i & (-i);
        }
        return s;
    }
    // range query [l, r)
    T query(int l, int r) { return query(r) - query(l); }
    // increase a[i] by v
    void update(int i, T v) {
        ++i;
        while (i <= n) {
            t[i] += v;
            i += i & (-i);
        }
    }
 
    // assumes f is monotonic - TT...TFF...F
    // returns the max r > 0 such that f(query([0, r)), r) is true
    // returns 0 if no such positive r exists
    template <class F>
    int max_right(F&& f) {
        // assert(f(0));
        T sum = 0;
        int pos = 0;
        for (int i = __lg(n); i >= 0; --i) {
            if (pos + (1 << i) <= n) {
                T s = sum + t[pos + (1 << i)];
                if (f(s, pos + (1 << i))) {
                    pos += (1 << i);
                    sum = s;
                }
            }
        }
        return pos;
    }
};
 
template <class T>
auto compress(const vector<T>& a) {
    int n = int(size(a));
    vector<pair<T, int>> p(n);
    for (int i = 0; i < n; ++i) p[i] = {a[i], i};
    sort(begin(p), end(p));
    vector<int> compressed(n);
    vector<T> vals;
    for (int k = 0, rnk = -1; k < n; ++k) {
        if (k == 0 or p[k - 1].first < p[k].first)
            vals.push_back(p[k].first), ++rnk;
        compressed[p[k].second] = rnk;
    }
    return make_pair(compressed, vals);
}
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        a = compress(a).first;
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[a[i]] = i;
        Fenwick<int> f(n, 1);
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            int p = pos[i];
            int left = f.query(p);
            int right = n - i - 1 - left;
            ans += min(left, right);
            f.update(p, -1);
        }
        cout << ans << '\n';
    }
}
 
