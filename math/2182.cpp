#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,bmi,bmi2")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif
 
namespace IO {
    constexpr bool UNSAFE = false;
    constexpr int GLOB_BUF_SIZE = 1 << 15;
#ifndef DEBUG
    #define CHANGE_DEFAULT_STREAMS
    static struct FastInput {
        FastInput() {
            if constexpr (UNSAFE) {
                chars_read = fread(buf, 1, BUF_SIZE, in);
                buf_pos = 0;
                buf[0] = (chars_read == 0 ? -1 : buf[0]);
            }
        }
        static constexpr int BUF_SIZE = GLOB_BUF_SIZE;
        char buf[BUF_SIZE];
        size_t chars_read = 0;
        size_t buf_pos = 0;
        FILE* in = stdin;
        char cur = 0;
        inline char get_char() {
            if constexpr (!UNSAFE) {
                if (buf_pos >= chars_read) {
                    chars_read = fread(buf, 1, BUF_SIZE, in);
                    buf_pos = 0;
                    buf[0] = (chars_read == 0 ? -1 : buf[0]);
                }
            }
            return cur = buf[buf_pos++];
        }
        template <typename T>
        inline FastInput* tie(T) {
            return this;
        }
        inline void sync_with_stdio(bool) {}
        inline explicit operator bool() { return cur != -1; }
        inline static bool is_blank(char c) { return c <= ' '; }
        inline bool skip_blanks() {
            while (is_blank(cur) && cur != -1) get_char();
            return cur != -1;
        }
        inline FastInput& operator>>(char& c) {
            skip_blanks();
            c = cur;
            get_char();
            return *this;
        }
        inline FastInput& operator>>(std::string& s) {
            if (skip_blanks()) {
                s.clear();
                do {
                    s += cur;
                } while (!is_blank(get_char()));
            }
            return *this;
        }
        template <typename T>
        inline FastInput& read_integer(T& n) {
            // unsafe, doesn't check that characters are actually digits
            n = 0;
            if (skip_blanks()) {
                int sign = +1;
                if (cur == '-') {
                    sign = -1;
                    get_char();
                }
                do {
                    n += n + (n << 3) + cur - '0';
                } while (!is_blank(get_char()));
                n *= sign;
            }
            return *this;
        }
        template <typename T>
        inline typename std::enable_if<std::is_integral<T>::value,
                                       FastInput&>::type
        operator>>(T& n) {
            return read_integer(n);
        }
    #if !defined(_WIN32) || defined(_WIN64)
        inline FastInput& operator>>(__int128& n) { return read_integer(n); }
    #endif
        template <typename T>
        inline typename std::enable_if<std::is_floating_point<T>::value,
                                       FastInput&>::type
        operator>>(T& n) {
            // not sure if really fast, for compatibility only
            n = 0;
            if (skip_blanks()) {
                std::string s;
                (*this) >> s;
                sscanf(s.c_str(), "%lf", &n);
            }
            return *this;
        }
    } fast_input;
    #define cin IO::fast_input
    static struct FastOutput {
        static constexpr int BUF_SIZE = GLOB_BUF_SIZE;
        char buf[BUF_SIZE];
        size_t buf_pos = 0;
        static constexpr int TMP_SIZE = GLOB_BUF_SIZE;
        char tmp[TMP_SIZE];
        FILE* out = stdout;
        inline void put_char(char c) {
            buf[buf_pos++] = c;
            if (buf_pos == BUF_SIZE) {
                fwrite(buf, 1, buf_pos, out);
                buf_pos = 0;
            }
        }
        ~FastOutput() { fwrite(buf, 1, buf_pos, out); }
        inline FastOutput& operator<<(char c) {
            put_char(c);
            return *this;
        }
        inline FastOutput& operator<<(const char* s) {
            while (*s) put_char(*s++);
            return *this;
        }
        inline FastOutput& operator<<(const std::string& s) {
            for (auto x : s) put_char(x);
            return *this;
        }
        template <typename T>
        inline char* integer_to_string(T n) {
            // beware of TMP_SIZE
            char* p = tmp + TMP_SIZE - 1;
            if (n == 0)
                *--p = '0';
            else {
                bool is_negative = false;
                if (n < 0) {
                    is_negative = true;
                    n = -n;
                }
                while (n > 0) {
                    *--p = (char)('0' + n % 10);
                    n /= 10;
                }
                if (is_negative) *--p = '-';
            }
            return p;
        }
        template <typename T>
        inline typename std::enable_if<std::is_integral<T>::value, char*>::type
        stringify(T n) {
            return integer_to_string(n);
        }
    #if !defined(_WIN32) || defined(_WIN64)
        inline char* stringify(__int128 n) { return integer_to_string(n); }
    #endif
        template <typename T>
        inline typename std::enable_if<std::is_floating_point<T>::value,
                                       char*>::type
        stringify(T n) {
            sprintf(tmp, "%.17f", n);
            return tmp;
        }
        template <typename T>
        inline FastOutput& operator<<(const T& n) {
            auto p = stringify(n);
            for (; *p != 0; p++) put_char(*p);
            return *this;
        }
    } fast_output;
    #define cout IO::fast_output
#endif
}  // namespace IO
 
using ll = int64_t;
using ld = long double;
 
constexpr int mod = int(1e9) + 7;
constexpr int nttmod = 998'244'353;
 
template <std::uint32_t P>
struct ModInt32 {
   public:
    using i32 = std::int32_t;
    using u32 = std::uint32_t;
    using i64 = std::int64_t;
    using u64 = std::uint64_t;
    using m32 = ModInt32;
 
   private:
    u32 v;
    static constexpr u32 get_r() {
        u32 iv = P;
        for (u32 i = 0; i != 4; ++i) iv *= 2U - P * iv;
        return -iv;
    }
    static constexpr u32 r = get_r(), r2 = -u64(P) % P;
    static_assert((P & 1) == 1);
    static_assert(-r * P == 1);
    static_assert(P < (1 << 30));
    static constexpr u32 pow_mod(u32 x, u64 y) {
        u32 res = 1;
        for (; y != 0; y >>= 1, x = u64(x) * x % P)
            if (y & 1) res = u64(res) * x % P;
        return res;
    }
    static constexpr u32 reduce(u64 x) {
        return (x + u64(u32(x) * r) * P) >> 32;
    }
    static constexpr u32 norm(u32 x) { return x - (P & -(x >= P)); }
 
   public:
    static constexpr u32 get_pr() {
        u32 tmp[32] = {}, cnt = 0;
        const u64 phi = P - 1;
        u64 m = phi;
        for (u64 i = 2; i * i <= m; ++i)
            if (m % i == 0) {
                tmp[cnt++] = i;
                while (m % i == 0) m /= i;
            }
        if (m != 1) tmp[cnt++] = m;
        for (u64 res = 2; res != P; ++res) {
            bool flag = true;
            for (u32 i = 0; i != cnt && flag; ++i)
                flag &= pow_mod(res, phi / tmp[i]) != 1;
            if (flag) return res;
        }
        return 0;
    }
    constexpr ModInt32() : v(0){};
    ~ModInt32() = default;
    constexpr ModInt32(u32 _v) : v(reduce(u64(_v) * r2)) {}
    constexpr ModInt32(i32 _v) : v(reduce(u64(_v % P + P) * r2)) {}
    constexpr ModInt32(u64 _v) : v(reduce((_v % P) * r2)) {}
    constexpr ModInt32(i64 _v) : v(reduce(u64(_v % P + P) * r2)) {}
    constexpr ModInt32(const m32& rhs) : v(rhs.v) {}
    constexpr u32 get() const { return norm(reduce(v)); }
    explicit constexpr operator u32() const { return get(); }
    explicit constexpr operator i32() const { return i32(get()); }
    constexpr m32& operator=(const m32& rhs) { return v = rhs.v, *this; }
    constexpr m32 operator-() const {
        m32 res;
        return res.v = (P << 1 & -(v != 0)) - v, res;
    }
    constexpr m32 inv() const { return pow(P - 2); }
    constexpr m32& operator+=(const m32& rhs) {
        return v += rhs.v - (P << 1), v += P << 1 & -(v >> 31), *this;
    }
    constexpr m32& operator-=(const m32& rhs) {
        return v -= rhs.v, v += P << 1 & -(v >> 31), *this;
    }
    constexpr m32& operator*=(const m32& rhs) {
        return v = reduce(u64(v) * rhs.v), *this;
    }
    constexpr m32& operator/=(const m32& rhs) {
        return this->operator*=(rhs.inv());
    }
    friend constexpr m32 operator+(const m32& lhs, const m32& rhs) {
        return m32(lhs) += rhs;
    }
    friend constexpr m32 operator-(const m32& lhs, const m32& rhs) {
        return m32(lhs) -= rhs;
    }
    friend constexpr m32 operator*(const m32& lhs, const m32& rhs) {
        return m32(lhs) *= rhs;
    }
    friend constexpr m32 operator/(const m32& lhs, const m32& rhs) {
        return m32(lhs) /= rhs;
    }
    friend constexpr bool operator==(const m32& lhs, const m32& rhs) {
        return norm(lhs.v) == norm(rhs.v);
    }
    friend constexpr bool operator!=(const m32& lhs, const m32& rhs) {
        return norm(lhs.v) != norm(rhs.v);
    }
    friend constexpr std::istream& operator>>(std::istream& is, m32& rhs) {
        return is >> rhs.v, rhs.v = reduce(u64(rhs.v) * r2), is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os,
                                              const m32& rhs) {
        return os << rhs.get();
    }
    constexpr m32 pow(i64 y) const {
        // assumes P is a prime
        i64 rem = y % (P - 1);
        if (y > 0 && rem == 0)
            y = P - 1;
        else
            y = rem;
        m32 res(1), x(*this);
        for (; y != 0; y >>= 1, x *= x)
            if (y & 1) res *= x;
        return res;
    }
};
 
// using mint = ModInt32<nttmod>;
using mint = ModInt32<mod>;
 
using namespace std;
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<pair<int, int>> factorization(n);
        bool is_square = true;
        for (auto& [p, x] : factorization)
            cin >> p >> x, is_square &= (x % 2 == 0);
 
        mint divs = 1;
        for (auto [p, x] : factorization) divs *= x + 1;
        cout << divs.get() << ' ';
 
        mint sum = 1;
        for (auto [p, x] : factorization)
            sum *= (mint(p).pow(x + 1) - 1) / mint(p - 1);
        cout << sum.get() << ' ';
 
        if (is_square) {
            mint ans = 1;
            ll final_pow = 1;
            for (auto [p, x] : factorization) {
                ans *= mint(p).pow(x / 2);
                final_pow *= x + 1;
                final_pow %= mod - 1;
            }
            ans = ans.pow(final_pow);
            cout << ans.get() << '\n';
        } else {
            mint ans = 1;
            bool divided = false;
            ll final_pow = 1;
            for (auto [p, x] : factorization) {
                ans *= mint(p).pow(x);
                if (x % 2 == 1 && !divided) {
                    divided = true;
                    final_pow *= (x + 1) / 2;
                } else {
                    final_pow *= (x + 1);
                }
                final_pow %= mod - 1;
            }
            ans = ans.pow(final_pow);
            cout << ans.get() << '\n';
        }
    }
}
