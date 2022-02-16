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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, q;
        cin >> n >> q;

        // a[l, r] -> ans = sum(a[l, r]) - sum_{i = l}^r max(a[l, i])
        vector<ll> a(n);
        for (auto& x : a) cin >> x;

        vector<ll> pre(n + 1);
        partial_sum(begin(a), end(a), begin(pre) + 1);

        constexpr int LG = 19;

        array<vector<pair<int, ll>>, LG> st{};
        for (auto& x : st) {
            x.resize(n);
            for (int i = 0; i < n; ++i) x[i] = {n, 0};
        }

        vector<int> next_greater(n, n);
        {
            stack<int> s;
            for (int i = n - 1; i >= 0; --i) {
                while (!s.empty() && a[s.top()] <= a[i]) s.pop();
                if (!s.empty()) next_greater[i] = s.top();
                s.push(i);
            }
        }

        // st[h][i] = {x, s}
        // x = 2^i-th element of greedy increasing chain to the right of i
        // s = sum_{j = i}^{x - 1} max(a[i..j])

        // build
        for (int i = 0; i < n; ++i)
            st[0][i] = {next_greater[i], a[i] * (next_greater[i] - i)};
        for (int h = 1; h < LG; ++h) {
            for (int i = 0; i < n; ++i) {
                auto [x, s] = st[h - 1][i];
                if (x == n) {
                    st[h][i] = {x, s};
                } else {
                    auto [x_new, s_new] = st[h - 1][x];
                    s += s_new;
                    x = x_new;
                    st[h][i] = {x, s};
                }
            }
        }

        auto query = [&st, &a](int l, int r) -> ll {
            // [l, r)
            int last = -1;
            for (int h = 0; h < LG; ++h) {
                if (st[h][l].first >= r) {
                    last = h;
                    break;
                }
            }
            ll ans = 0;
            for (int i = last - 1; i >= 0; --i) {
                auto [x, s] = st[i][l];
                if (x >= r) {
                    continue;
                } else {
                    ans += s;
                    l = x;
                }
            }
            if (l != r) ans += a[l] * (r - l);
            return ans;
        };

        while (q--) {
            int l, r;
            cin >> l >> r;
            --l;
            cout << query(l, r) - (pre[r] - pre[l]) << '\n';
        }
    }
}

