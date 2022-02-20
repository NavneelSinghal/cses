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

using ulll = __uint128_t;
using lll = __int128;
#ifdef __SIZEOF_INT128__
std::ostream& operator<<(std::ostream& os, __int128 const& value) {
    static char buffer[64];
    int index = 0;
    __uint128_t T = (value < 0) ? (-(value + 1)) + __uint128_t(1) : value;
    if (value < 0)
        os << '-';
    else if (T == 0)
        return os << '0';
    for (; T > 0; ++index) {
        buffer[index] = static_cast<char>('0' + (T % 10));
        T /= 10;
    }
    while (index > 0) os << buffer[--index];
    return os;
}
std::istream& operator>>(std::istream& is, __int128& T) {
    static char buffer[64];
    is >> buffer;
    std::size_t len = strlen(buffer), index = 0;
    T = 0;
    int mul = 1;
    if (buffer[index] == '-') ++index, mul *= -1;
    for (; index < len; ++index)
        T = T * 10 + static_cast<int>(buffer[index] - '0');
    T *= mul;
    return is;
}
#endif

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<pair<ll, ll>> points(n);
#define x first
#define y second
        for (auto& [x, y] : points) cin >> x >> y;
        lll ans = points[n - 1].x * points[0].y - points[0].x * points[n - 1].y;
        for (int i = 0; i + 1 < n; ++i)
            ans +=
                points[i].x * points[i + 1].y - points[i + 1].x * points[i].y;
        if (ans < 0) ans = -ans;
        // ans = 2 * area = 2 * interior + boundary - 2
        ans += 2;
        // count boundary points
        ll boundary = 0;
        for (int i = 0; i < n; ++i) {
            auto [x1, y1] = points[i];
            auto [x2, y2] = points[i == n - 1 ? 0 : i + 1];
            x2 -= x1;
            y2 -= y1;
            boundary += gcd(x2, y2);
        }
        cout << (ans - boundary) / 2 << ' ' << boundary << '\n';
    }
}
