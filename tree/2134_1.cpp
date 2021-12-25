#ifndef LOCAL
    #pragma GCC optimize("O3")
    #pragma GCC optimize("unroll-loops")
    #pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
#endif
 
#ifdef DEBUG
    #include "debug/bits/stdc++.h"
    #include "debug/ext/pb_ds/assoc_container.hpp"
    #include "debug/ext/pb_ds/tree_policy.hpp"
#else
    #include "bits/stdc++.h"
    #include "ext/pb_ds/assoc_container.hpp"
    #include "ext/pb_ds/tree_policy.hpp"
#endif
// #include <ext/rope>
 
using namespace std;
using namespace __gnu_pbds;
// using namespace __gnu_cxx;
 
using ll = long long;
using ull = unsigned long long;
using ld = long double;
 
#ifdef DEBUG
    #include "debug/debug.hpp"
#else
    #define debug(...) 0
#endif
#ifdef TIMING
    #include "debug/timing.hpp"
#else
// clang-format off
struct Stopwatch { Stopwatch(const string &s = "") {} void reset(){}
    void pause(){} void play(){} void print(){} ll elapsed() { return 0; }; };
// clang-format on
#endif
 
constexpr int inf = int(1e9);
constexpr ll linf = ll(3e18L);
constexpr ld eps = 1e-9;
const ld pi = acosl(-1.0);
 
template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
 
void setIO(string name = "") {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    cout << setprecision(20) << fixed;
    if (name.size() == 0) return;
    ignore = freopen((name + ".in").c_str(), "r", stdin);
    ignore = freopen((name + ".out").c_str(), "w", stdout);
}
 
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
 
constexpr int mod = int(1e9) + 7;
constexpr int nttmod = 998'244'353;
 
template <uint32_t Modulus>
class Modular {
    using M = Modular;
 
   public:
    static_assert(int(Modulus) >= 1, "Modulus must be in the range [1, 2^31)");
    static constexpr int modulus() { return Modulus; }
    static M raw(uint32_t v) { return *reinterpret_cast<M*>(&v); }
    Modular() : v_(0) {}
    Modular(int64_t v) : v_((v %= Modulus) < 0 ? v + Modulus : v) {}
    template <class T>
    explicit operator T() const {
        return v_;
    }
    M& operator++() { return v_ = ++v_ == Modulus ? 0 : v_, *this; }
    M& operator--() { return --(v_ ? v_ : v_ = Modulus), *this; }
    M& operator*=(M o) { return v_ = uint64_t(v_) * o.v_ % Modulus, *this; }
    M& operator/=(M o) {
        auto [inv, gcd] = extgcd(o.v_, Modulus);
        assert(gcd == 1);
        return *this *= inv;
    }
    M& operator+=(M o) {
        return v_ = int(v_ += o.v_ - Modulus) < 0 ? v_ + Modulus : v_, *this;
    }
    M& operator-=(M o) {
        return v_ = int(v_ -= o.v_) < 0 ? v_ + Modulus : v_, *this;
    }
    friend M operator++(M& a, int) { return exchange(a, ++M(a)); }
    friend M operator--(M& a, int) { return exchange(a, --M(a)); }
    friend M operator+(M a) { return a; }
    friend M operator-(M a) { return a.v_ = a.v_ ? Modulus - a.v_ : 0, a; }
    friend M operator*(M a, M b) { return a *= b; }
    friend M operator/(M a, M b) { return a /= b; }
    friend M operator+(M a, M b) { return a += b; }
    friend M operator-(M a, M b) { return a -= b; }
    friend istream& operator>>(istream& is, M& x) {
        int64_t v;
        return is >> v, x = v, is;
    }
    friend ostream& operator<<(ostream& os, M x) { return os << x.v_; }
    friend bool operator==(M a, M b) { return a.v_ == b.v_; }
    friend bool operator!=(M a, M b) { return a.v_ != b.v_; }
 
   private:
    static pair<int, int> extgcd(int a, int b) {
        array<int, 2> x{1, 0};
        while (b) swap(x[0] -= a / b * x[1], x[1]), swap(a %= b, b);
        return {x[0], a};
    }
    uint32_t v_;
};
 
using mint = Modular<mod>;
 
// when using integers, keep overflow in mind
template <class T, class F = multiplies<T>>
T pwr(T a, long long n, F op = multiplies<T>(), T e = {1}) {
    // assert(n >= 0);
    T res = e;
    while (n) {
        if (n & 1) res = op(res, a);
        if (n >>= 1) a = op(a, a);
    }
    return res;
}
 
namespace IO {
 
#define CHANGE_DEFAULT_STREAMS
 
    static struct FastInput {
        static constexpr int BUF_SIZE = 1 << 14;
        char buf[BUF_SIZE];
        size_t chars_read = 0;
        size_t buf_pos = 0;
        FILE* in = stdin;
        char cur = 0;
 
        inline char get_char() {
            if (buf_pos >= chars_read) {
                chars_read = fread(buf, 1, BUF_SIZE, in);
                buf_pos = 0;
                buf[0] = (chars_read == 0 ? -1 : buf[0]);
            }
            return cur = buf[buf_pos++];
        }
 
        inline FastInput* tie(int) { return this; }
        inline FastInput* tie(nullptr_t) { return this; }
        inline void sync_with_stdio(bool) {}
 
        inline explicit operator bool() { return cur != -1; }
 
        inline static bool is_blank(char c) { return c <= ' '; }
 
        inline bool skip_blanks() {
            while (is_blank(cur) && cur != -1) {
                get_char();
            }
            return cur != -1;
        }
 
        inline FastInput& operator>>(char& c) {
            skip_blanks();
            c = cur;
            return *this;
        }
 
        inline FastInput& operator>>(string& s) {
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
        inline typename enable_if<is_integral<T>::value, FastInput&>::type
        operator>>(T& n) {
            return read_integer(n);
        }
 
#if !defined(_WIN32) || defined(_WIN64)
        inline FastInput& operator>>(__int128& n) { return read_integer(n); }
#endif
 
        template <typename T>
        inline typename enable_if<is_floating_point<T>::value, FastInput&>::type
        operator>>(T& n) {
            // not sure if really fast, for compatibility only
            n = 0;
            if (skip_blanks()) {
                string s;
                (*this) >> s;
                sscanf(s.c_str(), "%lf", &n);
            }
            return *this;
        }
    } fast_input;
 
#define cin IO::fast_input
 
    static struct FastOutput {
        static constexpr int BUF_SIZE = 1 << 14;
        char buf[BUF_SIZE];
        size_t buf_pos = 0;
        static constexpr int TMP_SIZE = 1 << 14;
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
            while (*s) {
                put_char(*s++);
            }
            return *this;
        }
 
        inline FastOutput& operator<<(const string& s) {
            for (int i = 0; i < (int)s.size(); i++) {
                put_char(s[i]);
            }
            return *this;
        }
 
        template <typename T>
        inline char* integer_to_string(T n) {
            // beware of TMP_SIZE
            char* p = tmp + TMP_SIZE - 1;
            if (n == 0) {
                *--p = '0';
            } else {
                bool is_negative = false;
                if (n < 0) {
                    is_negative = true;
                    n = -n;
                }
                while (n > 0) {
                    *--p = (char)('0' + n % 10);
                    n /= 10;
                }
                if (is_negative) {
                    *--p = '-';
                }
            }
            return p;
        }
 
        template <typename T>
        inline typename enable_if<is_integral<T>::value, char*>::type stringify(
            T n) {
            return integer_to_string(n);
        }
 
#if !defined(_WIN32) || defined(_WIN64)
        inline char* stringify(__int128 n) { return integer_to_string(n); }
#endif
 
        template <typename T>
        inline typename enable_if<is_floating_point<T>::value, char*>::type
        stringify(T n) {
            sprintf(tmp, "%.17f", n);
            return tmp;
        }
 
        template <typename T>
        inline FastOutput& operator<<(const T& n) {
            auto p = stringify(n);
            for (; *p != 0; p++) {
                put_char(*p);
            }
            return *this;
        }
    } fast_output;
 
#define cout IO::fast_output
}  // namespace IO
 
// clang-format off
template <class Base,
          class Node,
          class Update,
          class MakeNode,
          class CombineNodes,
          class ApplyUpdate,
          class ComposeUpdates = std::nullptr_t>
struct lazy_segtree {
    static constexpr bool is_lazy =
        !std::is_same<ComposeUpdates, std::nullptr_t>::value;
 
   public:
    template <typename... T>
    explicit lazy_segtree(int n, const Base& id_base, T... args)
        : lazy_segtree(std::vector<Base>(n, id_base), args...) {}
    explicit lazy_segtree(const std::vector<Base>& v,
                          const Node& _id_node,
                          const MakeNode& _make_node,
                          const CombineNodes& _combine,
                          const Update& _id_update,
                          const ApplyUpdate& _apply_update,
                          const ComposeUpdates& _compose_updates = nullptr)
        : _n(int(v.size())),
          make_node(_make_node),
          combine(_combine),
          id_node(_id_node),
          apply_update(_apply_update),
          id_update(_id_update),
          compose_updates(_compose_updates) {
        build(v);
    }
 
    void build(const std::vector<Base>& v) {
        _n = int(v.size());
        log = 0;
        while ((1 << log) < _n) ++log;
        size = 1 << log;
        d = std::vector<Node>(2 * size, id_node);
        if constexpr (is_lazy) lz = std::vector<Update>(size, id_update);
        for (int i = 0; i < _n; i++) d[size + i] = make_node(v[i], i);
        for (int i = size - 1; i >= 1; i--) update(i);
    }
 
    void set(int p, Node x) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
 
    Node get(int p) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
 
    Node query(int l, int r) {
        if (l == r) return id_node;
        l += size, r += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l) push(l >> i);
                if (((r >> i) << i) != r) push((r - 1) >> i);
            }
        Node sml = id_node, smr = id_node;
        while (l < r) {
            if (l & 1) sml = combine(sml, d[l++]);
            if (r & 1) smr = combine(d[--r], smr);
            l >>= 1, r >>= 1;
        }
        return combine(sml, smr);
    }
    Node all_query() { return d[1]; }
    void update(int p, Update f) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = apply_update(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void update(int l, int r, Update f) {
        if (l == r) return;
        l += size, r += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l) push(l >> i);
                if (((r >> i) << i) != r) push((r - 1) >> i);
            }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1, r >>= 1;
            }
            l = l2, r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
 
    template <class G>
    int max_right(int l, G g) {
        // assert(0 <= l && l <= _n);
        // assert(g(id_node));
        if (l == _n) return _n;
        l += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(l >> i);
        Node sm = id_node;
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(combine(sm, d[l]))) {
                while (l < size) {
                    if constexpr (is_lazy) push(l);
                    l = (2 * l);
                    if (g(combine(sm, d[l]))) {
                        sm = combine(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = combine(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }
 
    template <class G>
    int min_left(int r, G g) {
        // assert(0 <= r && r <= _n);
        // assert(g(id_node));
        if (r == 0) return 0;
        r += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push((r - 1) >> i);
        Node sm = id_node;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(combine(d[r], sm))) {
                while (r < size) {
                    if constexpr (is_lazy) push(r);
                    r = (2 * r + 1);
                    if (g(combine(d[r], sm))) {
                        sm = combine(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = combine(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
 
   private:
    int _n, size, log;
    std::vector<Node> d;
    std::vector<Update> lz;
    const MakeNode make_node;
    const CombineNodes combine;
    const Node id_node;
    const ApplyUpdate apply_update;
    const Update id_update;
    const ComposeUpdates compose_updates;
 
    void update(int k) { d[k] = combine(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, Update f) {
        d[k] = apply_update(f, d[k]);
        if constexpr (is_lazy)
            if (k < size) lz[k] = compose_updates(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        if constexpr (is_lazy) lz[k] = id_update;
    }
};

// clang-format off
template <class Base,
          class Node,
          class Update,
          class MakeNode,
          class CombineNodes,
          class ApplyUpdate,
          class ComposeUpdates = std::nullptr_t>
struct lazy_segtree {
    static constexpr bool is_lazy =
        !std::is_same<ComposeUpdates, std::nullptr_t>::value;

   public:
    template <typename... T>
    explicit lazy_segtree(int n, const Base& id_base, T... args)
        : lazy_segtree(std::vector<Base>(n, id_base), args...) {}
    explicit lazy_segtree(const std::vector<Base>& v,
                          const Node& _id_node,
                          const MakeNode& _make_node,
                          const CombineNodes& _combine,
                          const Update& _id_update,
                          const ApplyUpdate& _apply_update,
                          const ComposeUpdates& _compose_updates = nullptr)
        : _n(int(v.size())),
          make_node(_make_node),
          combine(_combine),
          id_node(_id_node),
          apply_update(_apply_update),
          id_update(_id_update),
          compose_updates(_compose_updates) {
        build(v);
    }

    void build(const std::vector<Base>& v) {
        _n = int(v.size());
        log = 0;
        while ((1 << log) < _n) ++log;
        size = 1 << log;
        d = std::vector<Node>(2 * size, id_node);
        if constexpr (is_lazy) lz = std::vector<Update>(size, id_update);
        for (int i = 0; i < _n; i++) d[size + i] = make_node(v[i], i);
        for (int i = size - 1; i >= 1; i--) update(i);
    }
    
    void set(int p, Node x) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; ++i) update(p >> i);
    }

    Node get(int p) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    Node query(int l, int r) {
        if (l == r) return id_node;
        l += size, r += size;
        int l_ctz = __builtin_ctz(l);
        int r_ctz = __builtin_ctz(r);
        if constexpr (is_lazy) {
            for (int i = log; i > l_ctz; --i) push(l >> i);
            for (int i = log; i > r_ctz; --i) push((r - 1) >> i);
        }
        Node sml = id_node, smr = id_node;
        while (l < r) {
            if (l & 1) sml = combine(sml, d[l++]);
            if (r & 1) smr = combine(d[--r], smr);
            l >>= 1, r >>= 1;
        }
        return combine(sml, smr);
    }
    Node all_query() { return d[1]; }
    void update(int p, Update f) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = apply_update(f, d[p]);
        for (int i = 1; i <= log; ++i) update(p >> i);
    }
    void update(int l, int r, Update f) {
        if (l == r) return;
        l += size, r += size;
        int l_ctz = __builtin_ctz(l);
        int r_ctz = __builtin_ctz(r);
        if constexpr (is_lazy) {
            for (int i = log; i > l_ctz; --i) push(l >> i);
            for (int i = log; i > r_ctz; --i) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1, r >>= 1;
            }
            l = l2, r = r2;
        }
        for (int i = l_ctz + 1; i <= log; ++i) update(l >> i);
        for (int i = r_ctz + 1; i <= log; ++i) update((r - 1) >> i);
    }

    template <bool (*g)(Node)>
    int max_right(int l) {
        return max_right(l, [](Node x) { return g(x); });
    }
    template <class G>
    int max_right(int l, G g) {
        // assert(0 <= l && l <= _n);
        // assert(g(id_node));
        if (l == _n) return _n;
        l += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(l >> i);
        Node sm = id_node;
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(combine(sm, d[l]))) {
                while (l < size) {
                    if constexpr (is_lazy) push(l);
                    l = (2 * l);
                    if (g(combine(sm, d[l]))) {
                        sm = combine(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = combine(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(Node)>
    int min_left(int r) {
        return min_left(r, [](Node x) { return g(x); });
    }
    template <class G>
    int min_left(int r, G g) {
        // assert(0 <= r && r <= _n);
        // assert(g(id_node));
        if (r == 0) return 0;
        r += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push((r - 1) >> i);
        Node sm = id_node;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(combine(d[r], sm))) {
                while (r < size) {
                    if constexpr (is_lazy) push(r);
                    r = (2 * r + 1);
                    if (g(combine(d[r], sm))) {
                        sm = combine(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = combine(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

   private:
    int _n, size, log;
    std::vector<Node> d;
    std::vector<Update> lz;
    const MakeNode make_node;
    const CombineNodes combine;
    const Node id_node;
    const ApplyUpdate apply_update;
    const Update id_update;
    const ComposeUpdates compose_updates;

    void update(int k) { d[k] = combine(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, Update f) {
        d[k] = apply_update(f, d[k]);
        if constexpr (is_lazy)
            if (k < size) lz[k] = compose_updates(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id_update;
    }
};
// clang-format on

// clang-format off
template <class Base,
          class Node,
          class Update,
          class MakeNode,
          class CombineNodes,
          class CombineDifferent,
          class ApplyUpdate,
          class ComposeUpdates = std::nullptr_t>
// clang-format on
struct NonCommutativeHLD {
    using graph = std::vector<std::vector<int>>;

    static constexpr bool vals_in_edges = false;

    // clang-format off
    NonCommutativeHLD(const graph& G, int root, std::vector<Base>& vertex_vals,
                      const Base& _id_base,
                      const Node& _id_node,
                      const MakeNode& _make_node,
                      const CombineNodes& _combine,
                      const CombineDifferent& _combine_different,
                      const Update& _id_update,
                      const ApplyUpdate& _apply_update,
                      const ComposeUpdates& _compose_updates = nullptr)
        // clang-format on
        : N((int)G.size()),
          g(G),
          par(N),
          start(N),
          depth(N),
          sz(N),
          in_time(N),
          combine(_combine),
          combine_different(_combine_different),
          id_node(_id_node),
          tree(0, _id_base, _id_node, _make_node, _combine, _id_update,
               _apply_update, _compose_updates) {
        par[root] = -1;
        timer = 0;
        dfs_sz(root);
        start[root] = root;
        dfs_hld(root);
        std::vector<Base> perm(N);
        for (int i = 0; i < N; ++i) perm[in_time[i]] = vertex_vals[i];
        tree.build(perm);
    }

    bool is_anc(int u, int v) {
        return in_time[u] <= in_time[v] && in_time[u] + sz[u] > in_time[v];
    }

    void update_path(int u, int v, Update val) {
        // should customize val if breaking into segments changes val
        int l = lca(u, v);
        // u -> l, l -> v
        while (u != -1 && is_anc(l, u)) {
            int ql = max(in_time[start[u]], in_time[l] + vals_in_edges);
            int qr = in_time[u] + 1;
            tree.update(ql, qr, val);
            u = par[start[u]];
        }
        while (v != -1 && is_anc(l, v)) {
            int ql = max(in_time[start[v]], in_time[l] + 1);
            int qr = in_time[v] + 1;
            tree.update(ql, qr, val);
            v = par[start[v]];
        }
    }
    Node query_path(int u, int v) {
        const int l = lca(u, v);
        // u -> l, l -> v
        Node res_l = id_node, res_r = id_node;
        while (u != -1 && is_anc(l, u)) {
            int ql = max(in_time[start[u]], in_time[l] + vals_in_edges);
            int qr = in_time[u] + 1;
            res_l = combine(tree.query(ql, qr), res_l);
            u = par[start[u]];
        }
        while (v != -1 && is_anc(l, v)) {
            int ql = max(in_time[start[v]], in_time[l] + 1);
            int qr = in_time[v] + 1;
            res_r = combine(tree.query(ql, qr), res_r);
            v = par[start[v]];
        }
        // these nodes have different orientation
        return combine_different(res_l, res_r);
    }
    Node query_vertex(int u) { return tree.get(in_time[u]); }
    void update_vertex(int u, Update val) { tree.update(in_time[u], val); }
    // subtree updates and queries might not even make sense
    void update_subtree(int u, Node val) {
        int l = in_time[u] + vals_in_edges;
        int r = in_time[u] + sz[u];
        tree.update(l, r, val);
    }
    Node query_subtree(int u) {
        return tree.query(in_time[u] + vals_in_edges, in_time[u] + sz[u]);
    }
    void dfs_sz(int u) {
        sz[u] = 1;
        for (auto& v : g[u]) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            g[v].erase(find(begin(g[v]), end(g[v]), u));
            dfs_sz(v);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
    void dfs_hld(int u) {
        in_time[u] = timer++;
        for (auto& v : g[u]) {
            start[v] = (v == g[u][0] ? start[u] : v);
            dfs_hld(v);
        }
    }
    int lca(int u, int v) {
        for (; start[u] != start[v]; v = par[start[v]])
            if (depth[start[u]] > depth[start[v]]) swap(u, v);
        return depth[u] < depth[v] ? u : v;
    }
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

   private:
    int N;
    graph g;
    std::vector<int> par, start, depth, sz, in_time;
    const CombineNodes combine;
    const CombineDifferent combine_different;
    const Node id_node;
    lazy_segtree<Base, Node, Update, MakeNode, CombineNodes, ApplyUpdate,
                 ComposeUpdates>
        tree;
    int timer;
};

/* usage sample
    struct Node {
        ll s1, s2, s3;
        int size;
        Node() : s1(0), s2(0), s3(0), size(0) {}
        Node(ll x) : s1(0), s2(x), s3(0), size(1) {}
        Node(ll _s1, ll _s2, ll _s3, int _size)
            : s1(_s1), s2(_s2), s3(_s3), size(_size) {}
    };
    const Node id_node = Node();
    using Base = ll;
    const Base id_base = 0;
    auto make_node = [&](const Base& val, int i) {
        return Node(val);
    };
    auto combine = [&](const Node& a, const Node& b) {
        return Node{a.s1 + b.s1 + a.size * b.s2, a.s2 + b.s2,
                    a.s3 + b.s3 + b.size * a.s2, a.size + b.size};
    };
    auto combine_different = [&](const Node& n1, const Node& n2) {
        auto n3 = n1;
        swap(n3.s1, n3.s3);
        return combine(n3, n2);
    };
    using Update = ll;
    const Update id_update = -inf;
    auto apply_update = [&](const Update& u, const Node& nd) {
        if (u == -inf) return nd;
        ll s1 = 1LL * nd.size * (nd.size - 1) / 2 * u;
        ll sum = nd.size * u;
        return Node{s1, sum, s1, nd.size};
    };

    // parameters: graph, root, vertex values, id_node, make_node, combine,
    // combine_different, id_update, apply_update, compose_updates
    //
    // for edges, change static constexpr thing in class
    //
    // for lazy segtree, pass compose_updates as well
    //
    NonCommutativeHLD hld(g, 0, weight, id_base, id_node, make_node, combine,
                          combine_different, id_update, apply_update);
*/
 
auto main() -> signed {
#ifdef CUSTOM_IO
    IO::IOinit();
#else
    #ifndef CHANGE_DEFAULT_STREAMS
    setIO();
    #endif
#endif
 
    int TESTS = 1;
    // cin >> TESTS;
 
    auto precompute = [&]() -> void {
    };
 
    auto solve = [&](int) -> void {
        Stopwatch stopwatch;
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        using Node = int;
        const Node id_node = -inf;
        using Base = int;
        const Base id_base = 0;
        auto make_node = [](const Base& val, int i) {
            return Node(val);
        };
        auto combine = [](const Node& a, const Node& b) {
            return max(a, b);
        };
        auto combine_different = [](const Node& n1, const Node& n2) {
            return max(n1, n2);
        };
        using Update = int;
        const Update id_update = 0;
        auto apply_update = [&](const Update& u, const Node& nd) {
            return u + (!u) * nd;
        };
        NonCommutativeHLD hld(g, 0, a, id_base, id_node, make_node, combine,
                combine_different, id_update, apply_update);
        while (q--) {
            int type;
            cin >> type;
            if (type == 1) {
                int s, x;
                cin >> s >> x;
                --s;
                hld.update_vertex(s, x);
            } else {
                int a, b;
                cin >> a >> b;
                --a, --b;
                cout << hld.query_path(a, b) << ' ';
            }
        }
        cout << '\n';
    };
 
    auto brute = [&](int w = 1) -> void {
        ignore = w;
    };
 
    ignore = brute;
    precompute();
    for (int _t = 1; _t <= TESTS; ++_t) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
        // brute(_t);
    }
    return 0;
}
