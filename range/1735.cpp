#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
 
#include <bits/stdc++.h>
 
namespace IO {
 
    using namespace std;
 
#ifndef DEBUG
 
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
 
#endif
 
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
 
using namespace std;
using ll = long long;
 
constexpr ll inf = 5e9;
 
/*
   explicit lazy_segtree(const std::vector<Base>& v,
                          const Node& _id_node,
                          const MakeNode& _make_node,
                          const CombineNodes& _combine,
                          const Update& _id_update,
                          const ApplyUpdate& _apply_update,
                          const ComposeUpdates& _compose_updates = nullptr)
 */
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << fixed << setprecision(10) << '\n';
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; ++_t) {
        int n, q;
        cin >> n >> q;
        vector<ll> a(n);
        for (auto&& _x : a) cin >> _x;
        struct Node {
            ll sum;
            int size;
        };
        const Node id_node = {0, 0};
        auto make_node = [](ll x, int i) {
            return Node{x, 1};
        };
        auto combine = [](const Node& a, const Node& b) {
            return Node{a.sum + b.sum, a.size + b.size};
        };
        struct Update {
            ll a, b;
        };
        const Update id_update = {1, 0};
        auto apply_update = [](const Update& u, const Node& a) {
            return Node{u.a * a.sum + u.b * a.size, a.size};
        };
        auto compose_updates = [](const Update& u, const Update& v) {
            return Update{u.a * v.a, u.a * v.b + u.b};
        };
        lazy_segtree st(a, id_node, make_node, combine, id_update, apply_update,
                        compose_updates);
        while (q--) {
            int type, a, b, x;
            cin >> type;
            switch (type) {
                case 1:
                    cin >> a >> b >> x;
                    st.update(a - 1, b, Update{1, x});
                    break;
                case 2:
                    cin >> a >> b >> x;
                    st.update(a - 1, b, Update{0, x});
                    break;
                case 3:
                    cin >> a >> b;
                    cout << st.query(a - 1, b).sum << '\n';
                    break;
            }
        }
    }
    return 0;
}
