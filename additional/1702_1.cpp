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
 
template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
 
template <class T, class U = T>
bool ckmin(T& a, U&& b) {
    return b < a ? a = std::forward<U>(b), true : false;
}
 
template <class T, class U = T>
bool ckmax(T& a, U&& b) {
    return a < b ? a = std::forward<U>(b), true : false;
}
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> preorder(n), inorder(n), inorder_pos(n);
        for (auto& x : preorder) cin >> x, --x;
        for (auto& x : inorder) cin >> x, --x;
        for (int i = 0; i < n; ++i) inorder_pos[inorder[i]] = i;
        struct node {
            array<int, 2> children;
            node() { fill(begin(children), end(children), -1); }
        };
        vector<node> g(n);
        const auto rec = [&](const auto& self, int preorder_left,
                             int preorder_right, int inorder_left,
                             int inorder_right) -> void {
            int root = preorder[preorder_left];
            int root_loc = inorder_pos[root];
            int left_size = root_loc - inorder_left;
            int right_size = inorder_right - root_loc;
            if (left_size > 0) {
                g[root].children[0] = preorder[preorder_left + 1];
                self(self, preorder_left + 1, preorder_left + left_size, inorder_left, root_loc - 1);
            }
            if (right_size > 0) {
                g[root].children[1] = preorder[preorder_left + left_size + 1];
                self(self, preorder_left + left_size + 1, preorder_right, root_loc + 1, inorder_right);
            }
        };
        rec(rec, 0, n - 1, 0, n - 1);
        const auto dfs = [&](const auto& self, int root) -> void {
            if (g[root].children[0] != -1) self(self, g[root].children[0]);
            if (g[root].children[1] != -1) self(self, g[root].children[1]);
            cout << root + 1 << ' ';
        };
        dfs(dfs, preorder[0]);
        cout << '\n';
    }
}
