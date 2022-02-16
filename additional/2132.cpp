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
        // for explanation, see https://codeforces.com/blog/entry/77298
        int n;
        cin >> n;
        priority_queue<int> pq;
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            // push twice to add |X - x| to f(X)
            if (pq.empty()) {
                // first time
                pq.push(x);  // no need to push twice as x = rightmost point
            } else {
                if (pq.top() > x) {
                    // claim: last slope is 0 (else contradiction)
                    // so we need to only add pq.top() - x to the answer for min
                    ans += pq.top() - x;
                    // now add |X - x|
                    pq.push(x), pq.push(x);
                    // remove rightmost point
                    pq.pop();
                } else {
                    pq.push(x);  // no need to push twice
                }
            }
        }
        cout << ans << '\n';
    }
}

