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
 
namespace BITSET {
    template <int N>
    struct Bitset {
       private:
        static constexpr uint64_t ONE = 1;
        static constexpr uint64_t ZERO = 0;
        static constexpr uint64_t ALL_MASK = ~ZERO;
        static constexpr int BITS = sizeof(uint64_t) * CHAR_BIT;
        static constexpr int ALL = BITS - 1;
        static constexpr int CAPACITY = (N + BITS - 1) / BITS;
        static constexpr int REMAINING = N & ALL;
        static constexpr uint64_t CLEANUP_MASK = ~(ALL_MASK << REMAINING);
        uint64_t a[CAPACITY];
        struct reference {
           private:
            int pos;
            uint64_t* a;
 
           public:
            reference(int p, uint64_t* aa) : pos(p), a(aa) {}
            reference& operator=(bool x) noexcept {
                if (x)
                    *a |= ONE << pos;
                else
                    *a &= ~(ONE << pos);
                return *this;
            }
            reference& operator=(const reference& x) noexcept {
                if ((*x.a >> x.pos) & 1)
                    *a |= ONE << pos;
                else
                    *a &= ~(ONE << pos);
                return *this;
            }
            operator bool() const noexcept { return (*a >> pos) & 1; }
            bool operator~() const noexcept { return !((*a >> pos) & 1); }
            reference& flip() noexcept { *a ^= ONE << pos; }
        };
 
        inline void cleanup() noexcept { a[CAPACITY - 1] &= CLEANUP_MASK; }
 
       public:
        constexpr Bitset() noexcept {
            static_assert(BITS == 64, "Won't work on this architecture");
            static_assert(N > 0,
                          "Size of parameter should be a positive integer");
            reset();
        };
 
        constexpr Bitset(uint64_t x) noexcept : Bitset() { a[0] = x; };
 
        constexpr Bitset(const std::string& x) : Bitset() {
#ifdef DEBUG
            if (x.size() > N * BITS)
                throw std::out_of_range(
                    "String is too large to convert to Bitset");
#endif
            int cur_loc = 0;
            int bit = 0;
            for (const auto& c : x) {
#ifdef DEBUG
                if (c != '0' && c != '1')
                    throw std::invalid_argument(
                        "String should consist of only 0s and 1s");
#endif
                a[cur_loc] |= uint64_t(c - '0') << (bit++);
                if (bit == BITS) bit = 0, ++cur_loc;
            }
        }
 
        constexpr Bitset(const Bitset& b) {
            std::copy(std::begin(b.a), std::end(b.a), std::begin(a));
        }
 
        bool operator==(const Bitset& b) const {
            return std::equal(std::begin(a), std::end(a), std::begin(b.a));
        }
 
        bool operator!=(const Bitset& b) const { return !(*this == b); }
 
        constexpr bool operator[](int pos) const {
            return (a[pos / BITS] >> (pos & ALL)) & 1;
        }
 
        reference operator[](int pos) {
#ifdef DEBUG
            assert(("Bitset index out of range, UB", pos >= 0 && pos < N));
#endif
            return reference(pos & ALL, a + pos / BITS);
        }
 
        std::string to_string() const {
            std::string s(N, '0');
            auto it = s.data() + N - 1;
            for (int i = 0; i < N; ++i)
                *(it--) += (a[i / BITS] >> (i & ALL)) & 1;
            return s;
        }
 
        int count() const noexcept {
            int ans = 0;
            for (int i = 0; i < CAPACITY; ++i)
                ans += __builtin_popcountll(a[i]);
            return ans;
        }
 
        int size() const noexcept { return N; }
 
#define IMPLEMENT(op)                                      \
    Bitset& operator op(const Bitset& b) noexcept {        \
        for (int i = 0; i < CAPACITY; ++i) a[i] op b.a[i]; \
        return *this;                                      \
    }
        IMPLEMENT(&=)
        IMPLEMENT(|=)
        IMPLEMENT(^=)
#undef IMPLEMENT
        Bitset& flip() noexcept {
            for (int i = 0; i < CAPACITY; ++i) a[i] = ~a[i];
            cleanup();
            return *this;
        }
        Bitset operator~() const noexcept { return Bitset<N>(*this).flip(); }
 
        Bitset& operator<<=(int n) noexcept {
            if (n > N) {
                reset();
                return *this;
            }
            if (__builtin_expect(n != 0, 1)) {
                const int loc = n / BITS;
                const int pos = n & ALL;
                if (pos == 0)
                    for (int i = CAPACITY - 1; i >= loc; --i) a[i] = a[i - loc];
                else {
                    const int complement = BITS - pos;
                    for (int i = CAPACITY - 1; i > loc; --i)
                        a[i] = (a[i - loc] << pos) |
                               (a[i - loc - 1] >> complement);
                    a[loc] = a[0] << pos;
                }
                std::fill(std::begin(a), std::begin(a) + loc, 0);
                cleanup();
            }
            return *this;
        }
 
        // 01000 -> 00100
        Bitset& operator>>=(int n) noexcept {
            if (n > N) return reset(), *this;
            if (__builtin_expect(n != 0, 1)) {
                const int loc = n / BITS;
                const int pos = n & ALL;
                const int l = CAPACITY - 1 - loc;
                if (pos == 0)
                    for (int i = 0; i <= l; ++i) a[i] = a[i + loc];
                else {
                    const int complement = BITS - pos;
                    for (int i = 0; i < l; ++i)
                        a[i] = (a[i + loc] >> pos) |
                               (a[i + loc + 1] << complement);
                    a[l] = a[CAPACITY - 1] >> pos;
                }
                std::fill(std::begin(a) + l + 1, std::end(a), 0);
                cleanup();
            }
            return *this;
        }
 
        Bitset operator<<(int n) const noexcept {
            return Bitset<N>(*this) <<= n;
        }
 
        Bitset operator>>(int n) const noexcept {
            return Bitset<N>(*this) >>= n;
        }
 
        void reset() noexcept { std::fill(std::begin(a), std::end(a), 0); }
 
        void set() noexcept {
            std::fill(std::begin(a), std::end(a), ALL_MASK);
            cleanup();
        }
 
        int find_first_set() const noexcept {
            for (int i = 0; i < CAPACITY; ++i) {
                uint64_t w = a[i];
                if (w) return i * BITS + __builtin_ctzll(w);
            }
            return N;
        }
 
        int find_first_unset() const noexcept {
            for (int i = 0; i < CAPACITY; ++i) {
                uint64_t w = ~a[i];
                if (w) return i * BITS + __builtin_ctzll(w);
            }
            return N;
        }
 
        int find_next_set(int i) const noexcept {
            ++i;
            if (i >= BITS * CAPACITY) return N;
            int loc = i / BITS;
            uint64_t w = a[loc] & (ALL_MASK << (i & ALL));
            if (w) return loc * BITS + __builtin_ctzll(w);
            for (++loc; loc < CAPACITY; ++loc) {
                w = a[loc];
                if (w) return loc * BITS + __builtin_ctzll(w);
            }
            return N;
        }
 
        int find_next_unset(int i) const noexcept {
            ++i;
            if (i >= BITS * CAPACITY) return N;
            int loc = i / BITS;
            uint64_t w = (~a[loc]) & (ALL_MASK << (i & ALL));
            if (w) return loc * BITS + __builtin_ctzll(w);
            for (++loc; loc < CAPACITY; ++loc) {
                w = ~a[loc];
                if (w) return loc * BITS + __builtin_ctzll(w);
            }
            return N;
        }
 
        int find_last_set() const noexcept {
            for (int i = CAPACITY - 1; i >= 0; --i) {
                uint64_t w = a[i];
                if (w) return i * BITS + (ALL ^ __builtin_clzll(w));
            }
            return -1;
        }
 
        int find_last_unset() const noexcept {
            for (int i = CAPACITY - 1; i >= 0; --i) {
                uint64_t w = ~a[i];
                if (w) return i * BITS + (ALL ^ __builtin_clzll(w));
            }
            return -1;
        }
 
        // int find_kth_set(int k) const noexcept {}
 
        // int find_kth_unset(int k) const noexcept {}
 
        // int find_kth_next_set(int i, int k) const noexcept {}
 
        // int find_kth_next_unset(int i, int k) const noexcept {}
 
        // int find_kth_last_set(int k) const noexcept {}
 
        // int find_kth_last_unset(int k) const noexcept {}
 
        std::string to_string_debug() const {
            std::string s(CAPACITY * BITS, '0');
            for (int i = 0; i < CAPACITY * BITS; ++i)
                s[CAPACITY * BITS - 1 - i] += (a[i / BITS] >> (i & ALL)) & 1;
            return s;
        }
    };
 
    template <int N>
    inline Bitset<N> operator&(const Bitset<N>& x,
                               const Bitset<N>& y) noexcept {
        Bitset<N> result = x;
        result &= y;
        return result;
    }
    template <int N>
    inline Bitset<N> operator|(const Bitset<N>& x,
                               const Bitset<N>& y) noexcept {
        Bitset<N> result = x;
        result |= y;
        return result;
    }
    template <int N>
    inline Bitset<N> operator^(const Bitset<N>& x,
                               const Bitset<N>& y) noexcept {
        Bitset<N> result = x;
        result ^= y;
        return result;
    }
    template <int N>
    std::ostream& operator<<(std::ostream& os, const Bitset<N>& b) {
        return os << b.to_string();
    }
    template <int N>
    std::istream& operator>>(std::istream& os, Bitset<N>& b) {
        std::string s = "";
        os >> s;
        b = Bitset<N>(s);
        return os;
    }
 
}  // namespace BITSET
 
using namespace std;
 
using ll = int64_t;
using ld = long double;
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        using B = BITSET::Bitset<3000>;
        int n;
        cin >> n;
        vector<B> a;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            a.emplace_back(s);
        }
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ll cnt = (a[i] & a[j]).count();
                ans += cnt * (cnt - 1) / 2;
            }
        }
        cout << ans << '\n';
    }
}
