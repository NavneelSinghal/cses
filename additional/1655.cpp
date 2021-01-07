#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

struct trie {
    bool isleaf;
    trie* child[2];
};

trie* create() {
    trie* t = new trie();
    t->isleaf = false;
    memset(t->child, 0, sizeof t->child);
    return t;
}

void add(trie* root, int n) {
    int p = 0;
    for (int i = 31; ~i; --i) {
        p = (n >> i) & 1;
        if (root->child[p] == NULL) {
            root->child[p] = create();
        }
        root = root->child[p];
    }
}

void clean(trie* root) {
#ifdef CLEAN
    if (root == NULL) return;
    clean(root->child[0]);
    clean(root->child[1]);
    delete (root);
#endif
}

int maxxor(trie* root, int n) {
    int ans = 0;
    for (int i = 31; ~i; --i) {
        int p = (n >> i) & 1;
        if (root->child[p ^ 1] != NULL) {
            p ^= 1;
        }
        root = root->child[p];
        ans <<= 1;
        ans |= p ^ ((n >> i) & 1);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> pre(n + 1);
    for (int i = 0; i < n; ++i) {
        pre[i + 1] = pre[i] ^ a[i];
    }

    trie* t = create();
    add(t, 0);

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, maxxor(t, pre[i]));
        add(t, pre[i]);
    }

    clean(t);

    cout << ans << endl;
}
