#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n), stacks(n + 1, 2e9);

    // we play a game, where we have n + 1 stacks, initially with INF as the
    // only element in each, and we try to put elements in them in
    // non-increasing order and minimize the number of piles we greedily choose
    // the leftmost stack whose top number is greater than or equal to the
    // current number at hand, and put the current number on that stack then we
    // claim that the top elements consist of an increasing subsequence, and
    // this, in fact, is one of the longest increasing subsequences stacks are
    // represented by the last element we put on them
    //
    // another implementation that also retrieves the answer - 
    // https://sites.google.com/site/indy256/algo/lis_nlogn

    for (auto &x : a) cin >> x;
    for (int i = 0; i < n; ++i) {
        *lower_bound(stacks.begin(), stacks.end(), a[i]) = a[i];
    }
    for (int i = 0; i <= n; ++i) {
        if (stacks[i] == 2e9) {
            cout << i << '\n';
            return 0;
        }
    }
}
