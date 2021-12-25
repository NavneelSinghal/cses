#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
template <typename... T>
void debug(T&&...) {}
#endif
 
static const auto IOSetup = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    // std::cout << std::setprecision(6) << std::fixed;
    return nullptr;
}();
 
using ll = long long;
using ld = long double;
 
using namespace std;
 
// 0-based indexing for API
// 1-based indexing for internals
template <typename T>
struct Fenwick {
    int n;
    vector<T> t;
    Fenwick(int n) : n(n), t(n + 1) {}
    // prefix sum [0, i)
    T query(int i) {
        T s = 0;
        while (i) {
            s += t[i];
            i -= i & (-i);
        }
        return s;
    }
    // range query [l, r)
    T query(int l, int r) { return query(r) - query(l); }
    // increase a[i] by v
    void update(int i, T v) {
        ++i;
        while (i <= n) {
            t[i] += v;
            i += i & (-i);
        }
    }
 
    // assumes f is monotonic - TT...TFF...F
    // returns the max r > 0 such that f(query([0, r)), r) is true
    // returns 0 if no such positive r exists
    template <class F>
    int max_right(F&& f) {
        // assert(f(0));
        T sum = 0;
        int pos = 0;
        for (int i = __lg(n); i >= 0; --i) {
            if (pos + (1 << i) <= n) {
                T s = sum + t[pos + (1 << i)];
                if (f(s, pos + (1 << i))) {
                    pos += (1 << i);
                    sum = s;
                }
            }
        }
        return pos;
    }
};
 
int main() {
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        struct event {
            int time, index, type;
            bool operator<(const event& other) {
                return tie(time, type, index) <
                       tie(other.time, other.type, other.index);
            }
        };
        vector<event> events(2 * n);
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            events[2 * i] = {x, i, -1};
            events[2 * i + 1] = {y, i, 1};
        }
        sort(begin(events), end(events));
 
        Fenwick<int> f(n);
 
        vector<int> ans(n, -1);
        for (auto [time, index, type] : events) {
            if (type == 1) {
                // removal
                f.update(ans[index], -1);
            } else {
                // insertion
                int pos = f.max_right([](int sum, int r) { return sum == r; });
                ans[index] = pos;
                f.update(pos, 1);
            }
        }
        int total = *max_element(begin(ans), end(ans)) + 1;
        cout << total << '\n';
        for (auto x : ans) cout << x + 1 << ' ';
        cout << '\n';
    }
}
