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
        set<int> leaves;
        for (int i = 0; i < n; ++i)
            if (children[i] == 0) leaves.insert(i);
        for (int step = 0; step < n - 2; ++step) {
            int leaf = *leaves.begin();
            leaves.erase(leaf);
            int parent = prufer[step];
            children[parent]--;
            cout << leaf + 1 << ' ' << parent + 1 << '\n';
            if (children[parent] == 0) leaves.insert(parent);
        }
        assert((int)leaves.size() == 1);
        int u = *leaves.begin();
        cout << u + 1 << ' ' << prufer.back() + 1 << '\n';
    }
}
