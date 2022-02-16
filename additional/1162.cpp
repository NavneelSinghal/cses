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

ll solve_1(const vector<int>& a) {
    int n = (int)a.size();
    Fenwick<ll> f(n);
    ll ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        ans += f.query(a[i]);
        f.update(a[i], 1);
    }
    return ans;
}

ll solve_2(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> visited(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (visited[i]) continue;
        int cnt = 1;
        visited[i] = true;
        int j = a[i];
        while (!visited[j]) {
            cnt++;
            visited[j] = true;
            j = a[j];
        }
        ans += cnt - 1;
    }
    return ans;
}

template <class T, bool is_strict = true, bool return_indices = false,
          bool do_reserve = false>
auto get_lis_indices(const std::vector<T>& a) {
    std::vector<std::size_t> indices;
    const auto n = a.size();
    if constexpr (do_reserve) indices.reserve(n);
    const auto comparator = [&a](const std::size_t& x, const std::size_t& y) {
        return a[x] < a[y];
    };
    for (std::size_t i = 0; i < n; ++i) {
        std::size_t location;
        if constexpr (is_strict)
            location = std::lower_bound(std::begin(indices), std::end(indices),
                                        i, comparator) -
                       std::begin(indices);
        else
            location = std::upper_bound(std::begin(indices), std::end(indices),
                                        i, comparator) -
                       std::begin(indices);
        if (location == indices.size())
            indices.push_back(i);
        else
            indices[location] = i;
    }
    if constexpr (return_indices)
        return indices;
    else
        return indices.size();
}

ll solve_3(const vector<int>& a) {
    return a.size() - get_lis_indices(a);
}

ll solve_4(const vector<int>& a) {
    int n = (int)a.size();
    int last = n;
    for (int i = n - 1; i >= 0; --i)
        if (a[i] == last - 1) --last;
    return last;
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
        vector<int> a(n);
        for (auto& x : a) cin >> x, --x;
        cout << solve_1(a) << ' ' << solve_2(a) << ' ' << solve_3(a) << ' '
             << solve_4(a) << '\n';
    }
}

