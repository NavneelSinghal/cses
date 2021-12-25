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
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        struct node {
            array<int, 2> children;
            node() { fill(begin(children), end(children), -1); }
        };
        int ptr = 0;
        vector<node> nodes(1);
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            a[i] = a[i - 1] ^ x;
        }
        int ans = 0;
        const int root = 0;
        for (int i = 0; i < n; ++i) {
            int x = a[i];
            // insert x into the trie
            int curnode = root;
            for (int j = 30; j >= 0; --j) {
                int child = (x >> j) & 1;
                if (nodes[curnode].children[child] == -1) {
                    nodes[curnode].children[child] = int(nodes.size());
                    nodes.emplace_back();
                }
                curnode = nodes[curnode].children[child];
            }
            int c = a[i + 1];
            // find max xor
            curnode = root;
            int here = 0;
            for (int j = 30; j >= 0; --j) {
                int cur = (c >> j) & 1;
                if (nodes[curnode].children[cur ^ 1] != -1) {
                    curnode = nodes[curnode].children[cur ^ 1];
                    here ^= (1 << j);
                } else {
                    curnode = nodes[curnode].children[cur];
                }
            }
            ans = max(ans, here);
        }
        cout << ans << '\n';
    }
}
 
