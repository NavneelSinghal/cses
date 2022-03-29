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
        int a, b, n;
        cin >> a >> b >> n;
        vector<pair<ll, ll>> cost(n);
        for (auto& [x, y] : cost) cin >> x >> y;
        sort(rbegin(cost), rend(cost));
        // let i = last programmer
        // if j < i is jobless, give i's job to j to get a better sol
        // so it is optimal to have some prefix where all programmers are
        // and artists picked normally from the remaining
        // pick `a` programmers from prefix of size i
        // pick `i - a` artists using priority queue
        vector<ll> pre(a + b + 1);
        ll sum_programmers = 0;
        ll sum_artist_increases = 0;
        ll sum_bottom_a_artist_increases = 0;
        priority_queue<ll> pq;
        for (int i = 0; i < a; ++i) {
            sum_programmers += cost[i].first;
            ll artist_increase = cost[i].second - cost[i].first;
            sum_artist_increases += artist_increase;
            sum_bottom_a_artist_increases += artist_increase;
            pq.push(artist_increase);
        }
        // need to keep sum of top i - a artists
        // i.e. sum of bottom a artists
        for (int i = a; i <= a + b; ++i) {
            ll sum_top_i_a_artist_increases =
                sum_artist_increases - sum_bottom_a_artist_increases;
            pre[i] = sum_programmers + sum_top_i_a_artist_increases;
            if (i < a + b) {
                sum_programmers += cost[i].first;
                ll new_increase = cost[i].second - cost[i].first;
                sum_artist_increases += new_increase;
                if (a) {
                    if (new_increase < pq.top()) {
                        auto old_increase = pq.top();
                        sum_bottom_a_artist_increases +=
                            new_increase - old_increase;
                        pq.pop();
                        pq.push(new_increase);
                    }
                }
            }
        }

        priority_queue<ll>().swap(pq);
        vector<ll> suf(n + 1);
        // suf[i] = max skill of max(a + b - i, 0) artists in a suffix starting
        // from i + 1 1-indexed i = a to a + b
        suf[n] = 0;
        ll sum_bottom_n_a_b = 0;
        ll sum_all_artists = 0;
        for (int i = n; i > a + b; --i) {
            sum_all_artists += cost[i - 1].second;
            sum_bottom_n_a_b += cost[i - 1].second;
            pq.push(cost[i - 1].second);
        }
        // sum of bottom n - (a + b)
        for (int i = a + b; i >= a; --i) {
            suf[i] = sum_all_artists - sum_bottom_n_a_b;
            if (i > a) {
                ll new_artist_cost = cost[i - 1].second;
                sum_all_artists += new_artist_cost;
                if (n > a + b) {
                    if (new_artist_cost < pq.top()) {
                        auto old_artist_cost = pq.top();
                        sum_bottom_n_a_b += new_artist_cost - old_artist_cost;
                        pq.pop();
                        pq.push(new_artist_cost);
                    }
                }
            }
        }
        ll ans = 0;
        for (int i = a; i <= a + b; ++i) ans = max(pre[i] + suf[i], ans);
        cout << ans << '\n';
    }
}

