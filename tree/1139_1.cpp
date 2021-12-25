#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi2")
#endif
 
#include "bits/stdc++.h"
 
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif
 
using namespace std;
 
using ll = int64_t;
using ld = long double;
 
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
 
template <class T>
struct wavelet_matrix {
    using size_type = uint32_t;
    struct bit_vector {
        static constexpr size_type wsize = 64;
        static size_type rank64(uint64_t x, size_type i) {
            return __builtin_popcountll(x & ((1ULL << i) - 1));
        }
#pragma pack(4)
        struct block_t {
            uint64_t bit;
            size_type sum;
        };
#pragma pack()
        size_type n, zeros;
        std::vector<block_t> block;
        bit_vector(size_type _n = 0) : n(_n), block(n / wsize + 1) {}
        int operator[](size_type i) const {
            return block[i / wsize].bit >> i % wsize & 1;
        }
        void set(size_type i) {
            block[i / wsize].bit |= (uint64_t)1 << i % wsize;
        }
        void build() {
            for (size_type j = 0; j < n / wsize; ++j)
                block[j + 1].sum =
                    block[j].sum + __builtin_popcountll(block[j].bit);
            zeros = rank0(n);
        }
        size_type rank0(size_type i) const { return i - rank1(i); }
        size_type rank1(size_type i) const {
            auto&& e = block[i / wsize];
            return e.sum + rank64(e.bit, i % wsize);
        }
    };
    size_type n, lg;
    std::vector<T> a;
    std::vector<bit_vector> bv;
    wavelet_matrix(size_type _n = 0) : n(_n), a(n) {}
    wavelet_matrix(const std::vector<T>& _a) : n(_a.size()), a(_a) { build(); }
    T& operator[](size_type i) { return a[i]; }
    void build() {
        lg = std::__lg(std::max<T>(
                 *std::max_element(std::begin(a), std::end(a)), 1)) +
             1;
        bv.assign(lg, n);
        std::vector<T> cur = a, nxt(n);
        for (auto h = lg; h--;) {
            for (size_type i = 0; i < n; ++i)
                if (cur[i] >> h & 1) bv[h].set(i);
            bv[h].build();
            std::array<decltype(std::begin(nxt)), 2> it{
                std::begin(nxt), std::begin(nxt) + bv[h].zeros};
            for (size_type i = 0; i < n; ++i) *it[bv[h][i]]++ = cur[i];
            std::swap(cur, nxt);
        }
    }
    // find kth element in [l, r), 0 indexed
    T kth(size_type l, size_type r, size_type k) const {
        T res = 0;
        for (auto h = lg; h--;) {
            auto l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
            if (k < r0 - l0)
                l = l0, r = r0;
            else {
                k -= r0 - l0;
                res |= (T)1 << h;
                l += bv[h].zeros - l0;
                r += bv[h].zeros - r0;
            }
        }
        return res;
    }
    // count i in [l..r) satisfying a[i] < ub
    size_type count(size_type l, size_type r, T ub) const {
        if (ub >= (T)1 << lg) return r - l;
        if (ub <= 0) return 0;
        size_type res = 0;
        for (auto h = lg; h--;) {
            auto l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
            if (~ub >> h & 1)
                l = l0, r = r0;
            else {
                res += r0 - l0;
                l += bv[h].zeros - l0;
                r += bv[h].zeros - r0;
            }
        }
        return res;
    }
    // count i in [l..r) satisfying a[i] in [lb, ub)
    size_type count(size_type l, size_type r, T lb, T ub) const {
        return count(l, r, ub) - count(l, r, lb);
    }
};
 
template <class T>
auto compress(const vector<T>& a) {
    int n = int(size(a));
    vector<pair<T, int>> p(n);
#pragma GCC ivdep
    for (int i = 0; i < n; ++i) p[i] = {a[i], i};
    sort(begin(p), end(p));
    vector<int> compressed(n);
    vector<T> vals;
    for (int k = 0, rnk = -1; k < n; ++k) {
        if (k == 0 or p[k - 1].first < p[k].first)
            vals.push_back(p[k].first), ++rnk;
        compressed[p[k].second] = rnk;
    }
    return make_pair(compressed, vals);
}
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        int n;
        cin >> n;
        vector<int> c(n);
        for (auto& x : c) cin >> x;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<int> tin(n), sz(n), perm(n);
        int timer = 0;
        auto dfs = [&](auto self, int u, int p) -> void {
            perm[timer] = u;
            tin[u] = timer++;
            sz[u] = 1;
            for (auto v : g[u])
                if (v != p) self(self, v, u), sz[u] += sz[v];
        };
        dfs(dfs, 0, -1);
        c = compress(c).first;
        vector<int> nxt(n, n), pos(n, n);
        for (int i = n - 1; i >= 0; --i) {
            auto& x = pos[c[perm[i]]];
            nxt[i] = x, x = i;
        }
        wavelet_matrix wm(nxt);
        for (int i = 0; i < n; ++i) {
            int l = tin[i], r = tin[i] + sz[i];
            int le_r = wm.count(l, r, r);
            cout << r - l - le_r << ' ';
        }
        cout << '\n';
    }
}
 
