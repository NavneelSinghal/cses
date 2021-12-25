#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,bmi,bmi2")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif
 
using ll = int64_t;
using ld = long double;
 
using namespace std;
 
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
    // returns -1 if not found
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
                    b = s <= v;
                }
                if (b) {
                    sum = s;
                    pos += (1 << i);
                }
            }
        }
        if constexpr (next)
            return pos + 1;
        else
            return pos;
    }
};
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, k;
        cin >> n >> k;
        Fenwick<int> f(n);
        fill(begin(f.t) + 1, end(f.t), 1);
        int ans = k % n + 1;
        f.t[ans] = 0;
        for (int i = 1, j = 2; i <= n; ++i, j = (i & -i) + i)
            if (j <= n) f.t[j] += f.t[i];
        cout << ans << ' ';
        int p = ans;
        for (int i = n - 1; i > 0; --i) {
            p = (p + k - 1) % i + 1;
            int v = f.search<true, false>(p);
            cout << v << ' ';
            f.update(v, -1);
        }
        cout << '\n';
    }
}
