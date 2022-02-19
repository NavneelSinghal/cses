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

struct IOPre {
    static constexpr int TEN = 10, SZ = TEN * TEN * TEN * TEN;
    std::array<char, 4 * SZ> num;
    constexpr IOPre() : num{} {
        for (int i = 0; i < SZ; i++) {
            int n = i;
            for (int j = 3; j >= 0; j--) {
                num[i * 4 + j] = static_cast<char>(n % TEN + '0');
                n /= TEN;
            }
        }
    }
};
struct IO {
#if !HAVE_DECL_FREAD_UNLOCKED
    #define fread_unlocked fread
#endif
#if !HAVE_DECL_FWRITE_UNLOCKED
    #define fwrite_unlocked fwrite
#endif
    static constexpr int SZ = 1 << 17, LEN = 32, TEN = 10, HUNDRED = TEN * TEN,
                         THOUSAND = HUNDRED * TEN, TENTHOUSAND = THOUSAND * TEN,
                         MAGIC_MULTIPLY = 205, MAGIC_SHIFT = 11, MASK = 15,
                         TWELVE = 12, SIXTEEN = 16;
    static constexpr IOPre io_pre = {};
    std::array<char, SZ> input_buffer, output_buffer;
    int input_ptr_left, input_ptr_right, output_ptr_right;

    IO()
        : input_buffer{},
          output_buffer{},
          input_ptr_left{},
          input_ptr_right{},
          output_ptr_right{} {}
    IO(const IO&) = delete;
    IO(IO&&) = delete;
    IO& operator=(const IO&) = delete;
    IO& operator=(IO&&) = delete;

    ~IO() { flush(); }

    template <class T>
    struct is_char {
        static constexpr bool value = std::is_same_v<T, char>;
    };

    template <class T>
    struct is_bool {
        static constexpr bool value = std::is_same_v<T, bool>;
    };

    template <class T>
    struct is_string {
        static constexpr bool value =
            std::is_same_v<T, std::string> || std::is_same_v<T, const char*> ||
            std::is_same_v<T, char*> || std::is_same_v<std::decay_t<T>, char*>;
        ;
    };

    template <class T, class D = void>
    struct is_custom {
        static constexpr bool value = false;
    };

    template <class T>
    struct is_custom<T, std::void_t<typename T::internal_value_type>> {
        static constexpr bool value = true;
    };

    template <class T>
    struct is_default {
        static constexpr bool value = is_char<T>::value || is_bool<T>::value ||
                                      is_string<T>::value ||
                                      std::is_integral_v<T>;
    };

    template <class T, class D = void>
    struct is_iterable {
        static constexpr bool value = false;
    };

    template <class T>
    struct is_iterable<
        T, typename std::void_t<decltype(std::begin(std::declval<T>()))>> {
        static constexpr bool value = true;
    };

    template <class T, class D = void, class E = void>
    struct is_applyable {
        static constexpr bool value = false;
    };

    template <class T>
    struct is_applyable<T, std::void_t<typename std::tuple_size<T>::type>,
                        std::void_t<decltype(std::get<0>(std::declval<T>()))>> {
        static constexpr bool value = true;
    };

    template <class T>
    static constexpr bool needs_newline = (is_iterable<T>::value ||
                                           is_applyable<T>::value) &&
                                          (!is_default<T>::value);

    template <typename T, typename U>
    struct any_needs_newline {
        static constexpr bool value = false;
    };
    template <typename T>
    struct any_needs_newline<T, std::index_sequence<>> {
        static constexpr bool value = false;
    };
    template <typename T, std::size_t I, std::size_t... Is>
    struct any_needs_newline<T, std::index_sequence<I, Is...>> {
        static constexpr bool value =
            needs_newline<decltype(std::get<I>(std::declval<T>()))> ||
            any_needs_newline<T, std::index_sequence<Is...>>::value;
    };

    inline void load() {
        memmove(std::begin(input_buffer),
                std::begin(input_buffer) + input_ptr_left,
                input_ptr_right - input_ptr_left);
        input_ptr_right =
            input_ptr_right - input_ptr_left +
            static_cast<int>(fread_unlocked(
                std::begin(input_buffer) + input_ptr_right - input_ptr_left, 1,
                SZ - input_ptr_right + input_ptr_left, stdin));
        input_ptr_left = 0;
    }

    inline void read_char(char& c) {
        if (input_ptr_left + LEN > input_ptr_right) load();
        c = input_buffer[input_ptr_left++];
    }
    inline void read_string(std::string& x) {
        char c;
        while (read_char(c), c < '!') continue;
        x = c;
        while (read_char(c), c >= '!') x += c;
    }
    template <class T>
    inline std::enable_if_t<std::is_integral_v<T>, void> read_int(T& x) {
        if (input_ptr_left + LEN > input_ptr_right) load();
        char c = 0;
        do c = input_buffer[input_ptr_left++];
        while (c < '-');
        [[maybe_unused]] bool minus = false;
        if constexpr (std::is_signed<T>::value == true)
            if (c == '-') minus = true, c = input_buffer[input_ptr_left++];
        x = 0;
        while (c >= '0')
            x = x * TEN + (c & MASK), c = input_buffer[input_ptr_left++];
        if constexpr (std::is_signed<T>::value == true)
            if (minus) x = -x;
    }

    inline void skip_space() {
        if (input_ptr_left + LEN > input_ptr_right) load();
        while (input_buffer[input_ptr_left] <= ' ') input_ptr_left++;
    }

    inline void flush() {
        fwrite_unlocked(std::begin(output_buffer), 1, output_ptr_right, stdout);
        output_ptr_right = 0;
    }

    inline void write_char(char c) {
        if (output_ptr_right > SZ - LEN) flush();
        output_buffer[output_ptr_right++] = c;
    }

    inline void write_bool(bool b) {
        if (output_ptr_right > SZ - LEN) flush();
        output_buffer[output_ptr_right++] = b ? '1' : '0';
    }

    inline void write_string(const std::string& s) {
        for (auto x : s) write_char(x);
    }

    inline void write_string(const char* s) {
        while (*s) write_char(*s++);
    }

    inline void write_string(char* s) {
        while (*s) write_char(*s++);
    }

    template <typename T>
    inline std::enable_if_t<std::is_integral_v<T>, void> write_int(T x) {
        if (output_ptr_right > SZ - LEN) flush();
        if (!x) {
            output_buffer[output_ptr_right++] = '0';
            return;
        }
        if constexpr (std::is_signed<T>::value == true)
            if (x < 0) output_buffer[output_ptr_right++] = '-', x = -x;
        int i = TWELVE;
        std::array<char, SIXTEEN> buf{};
        while (x >= TENTHOUSAND) {
            memcpy(std::begin(buf) + i,
                   std::begin(io_pre.num) + (x % TENTHOUSAND) * 4, 4);
            x /= TENTHOUSAND;
            i -= 4;
        }
        if (x < HUNDRED) {
            if (x < TEN) {
                output_buffer[output_ptr_right++] = static_cast<char>('0' + x);
            } else {
                std::uint32_t q =
                    (static_cast<std::uint32_t>(x) * MAGIC_MULTIPLY) >>
                    MAGIC_SHIFT;
                std::uint32_t r = static_cast<std::uint32_t>(x) - q * TEN;
                output_buffer[output_ptr_right] = static_cast<char>('0' + q);
                output_buffer[output_ptr_right + 1] =
                    static_cast<char>('0' + r);
                output_ptr_right += 2;
            }
        } else {
            if (x < THOUSAND) {
                memcpy(std::begin(output_buffer) + output_ptr_right,
                       std::begin(io_pre.num) + (x << 2) + 1, 3),
                    output_ptr_right += 3;
            } else {
                memcpy(std::begin(output_buffer) + output_ptr_right,
                       std::begin(io_pre.num) + (x << 2), 4),
                    output_ptr_right += 4;
            }
        }
        memcpy(std::begin(output_buffer) + output_ptr_right,
               std::begin(buf) + i + 4, TWELVE - i);
        output_ptr_right += TWELVE - i;
    }
    template <typename T_>
    IO& operator<<(T_&& x) {
        using T = typename std::remove_cv<
            typename std::remove_reference<T_>::type>::type;
        static_assert(is_custom<T>::value or is_default<T>::value or
                      is_iterable<T>::value or is_applyable<T>::value);
        if constexpr (is_custom<T>::value) {
            write_int(x.get());
        } else if constexpr (is_default<T>::value) {
            if constexpr (is_bool<T>::value) {
                write_bool(x);
            } else if constexpr (is_string<T>::value) {
                write_string(x);
            } else if constexpr (is_char<T>::value) {
                write_char(x);
            } else if constexpr (std::is_integral_v<T>) {
                write_int(x);
            }
        } else if constexpr (is_iterable<T>::value) {
            // strings are immune
            using E = decltype(*std::begin(x));
            constexpr char sep = needs_newline<E> ? '\n' : ' ';
            int i = 0;
            for (const auto& y : x) {
                if (i++) write_char(sep);
                operator<<(y);
            }
        } else if constexpr (is_applyable<T>::value) {
            // strings are immune
            constexpr char sep =
                (any_needs_newline<
                    T, std::make_index_sequence<std::tuple_size_v<T>>>::value)
                    ? '\n'
                    : ' ';
            int i = 0;
            std::apply(
                [this, &sep, &i](auto const&... y) {
                    (((i++ ? write_char(sep) : void()), this->operator<<(y)),
                     ...);
                },
                x);
        }
        return *this;
    }
    template <typename T>
    IO& operator>>(T& x) {
        static_assert(is_custom<T>::value or is_default<T>::value or
                      is_iterable<T>::value or is_applyable<T>::value);
        static_assert(!is_bool<T>::value);
        if constexpr (is_custom<T>::value) {
            typename T::internal_value_type y;
            read_int(y);
            x = y;
        } else if constexpr (is_default<T>::value) {
            if constexpr (is_string<T>::value) {
                read_string(x);
            } else if constexpr (is_char<T>::value) {
                read_char(x);
            } else if constexpr (std::is_integral_v<T>) {
                read_int(x);
            }
        } else if constexpr (is_iterable<T>::value) {
            for (auto& y : x) operator>>(y);
        } else if constexpr (is_applyable<T>::value) {
            std::apply([this](auto&... y) { ((this->operator>>(y)), ...); }, x);
        }
        return *this;
    }

    IO* tie(std::nullptr_t) { return this; }
    void sync_with_stdio(bool) {}
};
IO io;
#define cin io
#define cout io

template <class T>
using pointer = T*;

constexpr int N = 200000;
int a[N];

constexpr int BUFSIZE = 2'000'000;

pair<int, int> p[N];
int compressed[N];
int vals[N];

int compress(int* a, int n) {
    for (int i = 0; i < n; ++i) p[i] = {a[i], i};
    sort(p, p + n);
    int vals_sz = 0;
    for (int k = 0, rnk = 0; k < n; ++k) {
        if (k == 0 or p[k - 1].first < p[k].first)
            vals[vals_sz++] = (p[k].first), ++rnk;
        compressed[p[k].second] = rnk;
    }
    return vals_sz;
}

ll sum_less[31][N + 1];
int cnt_less[31][N + 1];

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
    wavelet_matrix(T* _a, int _n) : n(_n), a(_a, _a + _n) { build(); }
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";

        // firstly note that if you sort the range a[l, r], then take the first
        // x such that 1 + sum(a[l, x - 1]) < a[x], you are done. also this can
        // happen at most log(max(a)) times, so break the interval [1, 2^30)
        // into [1, 2), [2, 4), ... and for each 2^x, find sum of elements in
        // [1, 2^x) in the range using the wavelet tree, and find the first
        // element >= 2^x in the wavelet tree

        // rather than wavelet tree to find the sum of elements and count the
        // number of elements < 2^i, we can just use a simple prefix array for
        // every power of 2

        int n, q;
        cin >> n >> q;
        ll sum = 0;
        for (int i = 0; i < n; ++i) cin >> a[i], sum += a[i];
        for (int i = 1; i <= 30; ++i) {
            for (int j = 0; j < n; ++j) {
                if (a[j] < (1 << i)) {
                    sum_less[i][j + 1] = sum_less[i][j] + a[j];
                    cnt_less[i][j + 1] = cnt_less[i][j] + 1;
                } else {
                    sum_less[i][j + 1] = sum_less[i][j];
                    cnt_less[i][j + 1] = cnt_less[i][j];
                }
            }
        }

        int vals_sz = compress(a, n);

        // a exists
        vector<int> query_positions{};
        for (ll i = 2; i <= (1LL << 30); i *= 2) {
            auto it = lower_bound(vals, vals + vals_sz, i);
            query_positions.push_back(it - vals);
        }

        for (int i = 0; i < vals_sz; ++i) a[i + 1] = vals[i];

        wavelet_matrix wm(compressed, n);

        while (q--) {
            int l, r;
            cin >> l >> r;
            ll ans = sum + 1;
            int prev_cnt_le = -1;
            for (int i = 1; i <= 30; ++i) {
                int pos = query_positions[i - 1];
                int cnt_le = cnt_less[i][r] - cnt_less[i][l - 1];
                ll sum_previous = sum_less[i][r] - sum_less[i][l - 1];
                if (cnt_le == r - l + 1) {
                    ans = sum_previous + 1;
                    break;
                } else if (cnt_le == 0) {
                    ans = 1;
                    break;
                }
                if (cnt_le == prev_cnt_le) continue;
                prev_cnt_le = cnt_le;
                int next_element = wm.kth(l - 1, r, cnt_le);
                if (sum_previous + 1 < a[next_element]) {
                    ans = sum_previous + 1;
                    break;
                }
            }
            cout << ans << '\n';
        }
    }
}

