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
        int n;
        cin >> n;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;

        auto element = [&](int i) -> ll {
            return a[i];
        };
        auto weight = [](int) -> ll {
            return 1;
        };

        auto weighted_isotonic_regression_l1_total_order =
            [](int n, const auto& element, const auto& weight) -> vector<ll> {
            struct Pair {
                ll pos, val;
                Pair(int pos_ = 0, int val_ = 0) : pos{pos_}, val{val_} {}
                bool operator<(const Pair& other) const {
                    return pos < other.pos;
                }
            };
            vector<ll> p(n);
            deque<Pair> pq;  // max heap
            for (int i = 0; i < n; ++i) {
                pq.emplace_back(element(i), 2 * weight(i));
                push_heap(begin(pq), end(pq));
                ll s = -weight(i);
                auto* b = &pq[0];
                while (s + b->val <= 0) {
                    s += b->val;
                    pop_heap(begin(pq), end(pq));
                    pq.pop_back();
                    b = &pq[0];
                }
                b->val += s;
                p[i] = b->pos;
            }
            for (int i = n - 2; i >= 0; --i) p[i] = min(p[i], p[i + 1]);
            return p;
        };
        auto p =
            weighted_isotonic_regression_l1_total_order(n, element, weight);
        ll ans = 0;
        for (int i = 0; i < n; ++i) ans += abs(a[i] - p[i]);
        cout << ans << '\n';
    }
}

