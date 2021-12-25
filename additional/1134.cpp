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
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        int n;
        cin >> n;
        vector<int> prufer(n - 2);
        for (auto& x : prufer) cin >> x, --x;
        vector<int> children(n);
        // note that at every point we remove a leaf, so the tree is never
        // disconnected. now root the tree at the vertex that the last leaf
        // was attached to
        children[prufer.back()]++;  // corresponding to the last remaining edge
        for (auto& x : prufer) children[x]++;
        int ptr = 0;
        while (ptr < n && children[ptr] > 0) ++ptr;
        assert(ptr < n);
        int cur_leaf = ptr;
        // [0, ptr] has at most 1 leaf
        for (auto v : prufer) {
            cout << v + 1 << ' ' << cur_leaf + 1 << '\n';
            --children[v];
            if (children[v] == 0) {
                if (v < ptr) {
                    cur_leaf = v;
                } else {
                    ++ptr;
                    while (ptr < n && children[ptr] > 0) ++ptr;
                    assert(ptr != n);
                    cur_leaf = ptr;
                }
            } else {
                ++ptr;
                while (ptr < n && children[ptr] > 0) ++ptr;
                assert(ptr != n);
                cur_leaf = ptr;
            }
        }
        // now only one leaf exists, and the final edge joins this to prufer.back()
        cout << prufer.back() + 1 << ' ' << cur_leaf + 1 << '\n';
    }
}
 
