#include "bits/stdc++.h"
using namespace std;
using ll = int64_t;
 
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
 
#define unordered_map __gnu_pbds::gp_hash_table
 
namespace hashing {
    using ull = uint64_t;
 
    static const ull FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();
 
    template <class T, class D = void>
    struct custom_hash {};
 
    // https://www.boost.org/doc/libs/1_55_0/doc/html/hash/combine.html
    template <class T>
    inline void hash_combine(ull& seed, const T& v) {
        custom_hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b97f4a7c15 + (seed << 12) + (seed >> 4);
    };
 
    // http://xorshift.di.unimi.it/splitmix64.c
    template <class T>
    struct custom_hash<
        T, typename std::enable_if<std::is_integral<T>::value>::type> {
        ull operator()(T v) const {
            ull x = v + 0x9e3779b97f4a7c15 + FIXED_RANDOM;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }
    };
 
    template <class T, size_t N>
    struct custom_hash<array<T, N>, void> {
        ull operator()(const array<T, N>& a) const {
            ull value = FIXED_RANDOM;
            for (auto& x : a) hash_combine(value, x);
            return value;
        }
    };
 
};  // namespace hashing
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n = (int)s.size();
    string vals, others;
    using F = array<int, 26>;
    F freq{};
    for (auto x : s) freq[x - 'a']++;
    for (int i = 0; i < 26; ++i)
        if (freq[i]) vals += char('a' + i);
    if (vals.size() > 1) others = vals.substr(1);
    ll ans = 0;
    F x{};
    unordered_map<F, int, hashing::custom_hash<F>> m;
    m[x]++;
    for (int i = 0; i < n; ++i) {
        if (s[i] == vals[0])
            for (auto c : others) x[c - 'a']--;
        else
            x[s[i] - 'a']++;
        ans += m[x];
        m[x]++;
    }
    cout << ans << '\n';
}
 
