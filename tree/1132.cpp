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
        vector<basic_string<int>> g(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        queue<int> q;
        q.push(0);
        vector<int> d(n, -1);
        d[0] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
 
        int left_endpoint = int(max_element(begin(d), end(d)) - begin(d));
        fill(begin(d), end(d), -1);
        q.push(left_endpoint);
        d[left_endpoint] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
 
        auto d_left = d;
 
        int right_endpoint = int(max_element(begin(d), end(d)) - begin(d));
        fill(begin(d), end(d), -1);
        q.push(right_endpoint);
        d[right_endpoint] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
 
        auto& d_right = d;
        for (int i = 0; i < n; ++i)
            cout << max(d_left[i], d_right[i]) << " \n"[i == n - 1];
    }
}
