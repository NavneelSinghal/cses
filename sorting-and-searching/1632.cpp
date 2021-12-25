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
 
int main() {
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, k;
        cin >> n >> k;
        vector<pair<int, int>> a(n);
        for (auto& [y, x] : a) cin >> x >> y;
        sort(begin(a), end(a));
        multiset<int> end_times;
        for (int i = 0; i < k; ++i) end_times.insert(0);
        int ans = 0;
        for (auto [end_time, start_time] : a) {
            auto it = end_times.lower_bound(-start_time);
            if (it == end_times.end()) continue;
            ans++;
            end_times.erase(it);
            end_times.insert(-end_time);
        }
        cout << ans << '\n';
    }
}
