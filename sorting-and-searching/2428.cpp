#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,bmi,bmi2,lzcnt")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif
 
using namespace std;
 
using ll = int64_t;
using ld = long double;
 
// 1-based indexing
template <typename T>
struct Fenwick {
    int n;
    vector<T> t;
    Fenwick(int n) : n(n), t(n + 1) {}
    // prefix_sum[0..i]
    T query(int i) {
        T s = 0;
        while (i) {
            s += t[i];
            i -= i & (-i);
        }
        return s;
    }
    // range query
    T query(int l, int r) { return query(r) - query(l - 1); }
    // increase a[i] by v
    void update(int i, T v) {
        while (i <= n) {
            t[i] += v;
            i += i & (-i);
        }
    }
    // if next = true, returns index of first element that is > or >=
    // if next = false, returns index of last element that is < or <=
    // returns -1 or n + 1 in appropriate cases
    // assumes everything in the fenwick tree is non-negative
    template <bool next, bool strict>
    int search(T v) {
        if (v == 0) {
            if constexpr (!next)
                return -int(strict);
            else if constexpr (!strict)
                return 0;
        } else if (v < 0) {
            return int(next) - 1;
        }
        T sum = 0;
        int pos = 0;
        for (int i = __lg(n); i >= 0; --i) {
            if (pos + (1 << i) <= n) {
                bool b = false;
                T s = sum + t[pos + (1 << i)];
                if constexpr (next != strict) {
                    b = s < v;
                } else {
                    b = !(v < s);
                }
                if (b) {
                    sum = s;
                    pos += (1 << i);
                }
            }
        }
        // sum = sum[0..pos] < or <= v, depending on strict
        if constexpr (next)
            return pos + 1;
        else
            return pos;
    }
};
 
template <class T>
auto compress(const vector<T>& a) {
    int n = int(size(a));
    vector<pair<T, int>> p(n);
#pragma GCC ivdep
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
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        vector<int> compressed, vals;
        tie(compressed, vals) = compress(a);
        vector<int> loc(vals.size(), -1);
        Fenwick<int> f(n);
        auto update = [&](int i) {
            auto ci = compressed[i];
            if (loc[ci] != -1) f.update(loc[ci] + 1, -1);
            loc[ci] = i;
            f.update(i + 1, 1);
        };
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            update(i);
            ans += i - f.search<true, true>(f.query(i + 1) - k - 1) + 1;
        }
        cout << ans << '\n';
    }
}
