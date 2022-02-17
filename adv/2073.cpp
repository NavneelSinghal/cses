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

namespace treap {

    // everything is 1-indexed

    std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());
    const int INF = 1e9;

    struct treap_node {
        int priority, value, cnt;
        bool is_reversed;
        treap_node *left_child, *right_child;
        treap_node(int v)
            : priority(std::uniform_int_distribution<int>(0, INF)(rng)),
              value(v),
              cnt(1),
              is_reversed(false),
              left_child(nullptr),
              right_child(nullptr) {}
    };

    using treap_node_ptr = treap_node*;

    int cnt(treap_node_ptr t) { return t ? t->cnt : 0; }

    void update_cnt(treap_node_ptr t) {
        if (t) {
            t->cnt = cnt(t->left_child) + cnt(t->right_child) + 1;
        }
    }

    void push(treap_node_ptr t) {
        if (t && t->is_reversed) {
            t->is_reversed = false;
            std::swap(t->left_child, t->right_child);
            if (t->left_child) t->left_child->is_reversed ^= true;
            if (t->right_child) t->right_child->is_reversed ^= true;
        }
    }

    void merge(treap_node_ptr& t, treap_node_ptr l, treap_node_ptr r) {
        push(l);
        push(r);
        if (!l || !r) {
            t = (l ? l : r);
        } else if (l->priority > r->priority) {
            merge(l->right_child, l->right_child, r);
            t = l;
        } else {
            merge(r->left_child, l, r->left_child);
            t = r;
        }
        update_cnt(t);
    }

    void split(treap_node_ptr t, treap_node_ptr& l, treap_node_ptr& r, int key,
               int add = 0) {
        if (!t) {
            l = r = 0;
            return;
        }
        push(t);
        int cur_key = add + cnt(t->left_child);
        if (key <= cur_key) {
            split(t->left_child, l, t->left_child, key, add);
            r = t;
        } else {
            split(t->right_child, t->right_child, r, key,
                  add + 1 + cnt(t->left_child));
            l = t;
        }
        update_cnt(t);
    }

    void insert(treap_node_ptr& t, int pos, int v) {
        treap_node_ptr t1, t2;
        split(t, t1, t2, pos - 1);
        merge(t1, t1, new treap_node(v));
        merge(t, t1, t2);
    }

    void erase(treap_node_ptr& t, int pos) {
        treap_node_ptr t1, t2, t3;
        split(t, t1, t2, pos - 1);
        split(t2, t2, t3, 1);
        merge(t, t1, t3);
    }

    void reverse(treap_node_ptr t, int l, int r) {
        treap_node_ptr t1, t2, t3;
        split(t, t1, t2, l - 1);  // one-indexed
        split(t2, t2, t3, r - l + 1);
        t2->is_reversed ^= true;
        merge(t, t1, t2);
        merge(t, t, t3);
    }

    void inorder_traversal(treap_node_ptr t, std::vector<int>& a) {
        if (!t) return;
        push(t);
        inorder_traversal(t->left_child, a);
        a.push_back(t->value);
        inorder_traversal(t->right_child, a);
    }

    void print_treap(treap_node_ptr t) {
        std::vector<int> v;
        inorder_traversal(t, v);
        for (auto x : v) std::cerr << x << ' ';
        std::cerr << '\n';
    }

}  // namespace treap

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        treap::treap_node_ptr root = nullptr;
        for (int i = 0; i < n; ++i) treap::insert(root, i + 1, s[i]);
        for (int i = 0; i < m; ++i) {
            int l, r;
            cin >> l >> r;
            treap::reverse(root, l, r);
        }
        vector<int> v;
        treap::inorder_traversal(root, v);
        for (auto x : v) cout << char(x);
        cout << '\n';
    }
}

