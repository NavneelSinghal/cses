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
    using internal_value_type = u32;
 
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
    friend m32 operator+(const m32& lhs, const m32& rhs) {
        return m32(lhs) += rhs;
    }
    friend m32 operator-(const m32& lhs, const m32& rhs) {
        return m32(lhs) -= rhs;
    }
    friend m32 operator*(const m32& lhs, const m32& rhs) {
        return m32(lhs) *= rhs;
    }
    friend m32 operator/(const m32& lhs, const m32& rhs) {
        return m32(lhs) /= rhs;
    }
    friend bool operator==(const m32& lhs, const m32& rhs) {
        return norm(lhs.v) == norm(rhs.v);
    }
    friend bool operator!=(const m32& lhs, const m32& rhs) {
        return norm(lhs.v) != norm(rhs.v);
    }
    friend std::istream& operator>>(std::istream& is, m32& rhs) {
        return is >> rhs.v, rhs.v = reduce(u64(rhs.v) * r2), is;
    }
    friend std::ostream& operator<<(std::ostream& os, const m32& rhs) {
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
 
using mint = ModInt32<mod>;
 
template <typename t>
struct matrix {
    int32_t rows, cols;
    vector<vector<t>> mat;
 
    // rows and columns
    matrix(int32_t r, int32_t c)
        : rows(r), cols(c), mat(vector<vector<t>>(r, vector<t>(c))){};
 
    // initializer list
    matrix(initializer_list<initializer_list<t>> l)
        : rows(l.size()), cols(l.begin()->size()) {
        mat = vector<vector<t>>(rows);
        int i = 0;
        for (auto& x : l) {
            mat[i] = x;
            ++i;
            assert(x.size() == cols);
        }
    };
 
    void fill(t val) {
        for (int32_t i = 0; i < rows; i++) {
            for (int32_t j = 0; j < cols; j++) {
                mat[i][j] = val;
            }
        }
    }
 
    void reset() { fill(0); }
 
    void setid() {
        assert(rows == cols);
        for (int32_t i = 0; i < rows; i++) {
            mat[i][i] = 1;
        }
    }
 
    static matrix id(int32_t n) {
        matrix m(n, n);
        m.setid();
        return m;
    }
 
    matrix operator+(const matrix& a) const {
        assert(rows == a.rows && cols == a.cols);
        matrix<t> res(rows, cols);
        for (int32_t i = 0; i < rows; i++) {
            for (int32_t j = 0; j < cols; j++) {
                res.mat[i][j] = mat[i][j] + a.mat[i][j];
            }
        }
    }
 
    matrix<t> operator*(const matrix<t>& a) const {
        assert(cols == a.rows);
        matrix<t> res(rows, a.cols);
        for (int32_t i = 0; i < rows; i++) {
            for (int32_t j = 0; j < a.cols; j++) {
                res.mat[i][j] = 0;
                for (int32_t k = 0; k < cols; k++) {
                    res.mat[i][j] += mat[i][k] * a.mat[k][j];
                }
            }
        }
        return res;
    }
 
    void operator+=(const matrix& a) { *this = *this + a; }
    void operator*=(const matrix& a) { *this = *this * a; }
 
    matrix<t> operator^(int32_t n) {
        matrix<t> ans(rows, cols);
        ans.setid();
        matrix<t> a = *this;
        while (n) {
            if (n & 1) ans *= a;
            a *= a;
            n >>= 1;
        }
        return ans;
    }
};
 
int main() {
    int _tests = 1;
    cin >> _tests;
 
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
 
        matrix start{{mint(1)}, {mint(1)}};
        matrix transition{{mint(4), mint(1)}, {mint(1), mint(2)}};
 
        matrix ans = (transition ^ (n - 1)) * start;
 
        cout << ans.mat[0][0] + ans.mat[1][0] << '\n';
    }
}
