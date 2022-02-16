#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC target("avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, q;
        cin >> n >> q;

        constexpr ll linf = 1e18L;

        // a[l, r] -> ans = sum(a[l, r]) - sum_{i = l}^r max(a[l, i])
        vector<ll> a(n + 1);
        for (int i = 0; i < n; ++i) cin >> a[i];
        a[n] = linf;

        vector<ll> pre(n + 1);
        partial_sum(begin(a), end(a), begin(pre));

        vector<vector<pair<int, int>>> query_at(n);
        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            --l, --r;
            query_at[l].emplace_back(r, i);
        }

        vector<ll> add(n);
        Fenwick<ll> f(n + 1);

        vector<ll> ans(n);

        deque<int> st{n};
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && a[i] >= a[st.front()]) {
                f.update(st.front(), -add[st.front()]);
                st.pop_front();
            }
            add[i] =
                (st.front() - 1 - i) * a[i] - (pre[st.front() - 1] - pre[i]);
            f.update(i, add[i]);
            st.push_front(i);
            for (auto [q_r, q_i] : query_at[i]) {
                int pos = int(upper_bound(st.begin(), st.end(), q_r) -
                              st.begin() - 1);
                ans[q_i] = (pos ? f.query(i, st[pos - 1] + 1) : 0) +
                           (q_r - st[pos]) * a[st[pos]] -
                           (pre[q_r] - pre[st[pos]]);
            }
        }

        for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    }
}

