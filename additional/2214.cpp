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
        inline FastInput* tie(T) { return this; }
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
 
static char buf[500 << 20];
void* operator new(size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void*)&buf[i -= s];
}
//void operator delete(void*) {}
void operator delete(void*) noexcept {}
void operator delete(void*, size_t) noexcept {}
 
template <class T>
struct ptr {
    unsigned ind;
    ptr(T* p = 0) : ind(p ? unsigned((char*)p - buf) : 0) {
        assert(ind < sizeof buf);
    }
    bool operator==(const ptr other) { return ind == other.ind; }
    T& operator*() const { return *(T*)(buf + ind); }
    T* operator->() const { return &**this; }
    T& operator[](int a) const { return (&**this)[a]; }
    explicit operator bool() const { return ind; }
};
 
namespace treap {
 
    std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());
    const int INF = 1e9;
 
    struct treap_node {
        int priority, value, cnt;
        bool is_reversed;
        ptr<treap_node> left_child, right_child;
        treap_node(int v)
            : priority(std::uniform_int_distribution<int>(0, INF)(rng)),
              value(v),
              cnt(1),
              left_child(nullptr),
              right_child(nullptr) {}
    };
 
    using treap_node_ptr = ptr<treap_node>;
 
    int cnt(treap_node_ptr t) { return t ? t->cnt : 0; }
 
    void update_cnt(treap_node_ptr t) {
        if (t) {
            t->cnt = cnt(t->left_child) + cnt(t->right_child) + 1;
        }
    }
 
    void push(treap_node_ptr t) {
        if (t && t->is_reversed) {
            t->is_reversed = false;
            std::swap(t->left_child, t->right_child);
            if (t->left_child) t->left_child->is_reversed ^= true;
            if (t->right_child) t->right_child->is_reversed ^= true;
        }
    }
 
    void merge(treap_node_ptr& t, treap_node_ptr l, treap_node_ptr r) {
        push(l);
        push(r);
        if (!l || !r) {
            t = (l ? l : r);
        } else if (l->priority > r->priority) {
            merge(l->right_child, l->right_child, r);
            t = l;
        } else {
            merge(r->left_child, l, r->left_child);
            t = r;
        }
        update_cnt(t);
    }
 
    void split(treap_node_ptr t, treap_node_ptr& l, treap_node_ptr& r, int key,
               int add = 0) {
        if (!t) {
            l = r = 0;
            return;
        }
        push(t);
        int cur_key = add + cnt(t->left_child);
        if (key <= cur_key) {
            split(t->left_child, l, t->left_child, key, add);
            r = t;
        } else {
            split(t->right_child, t->right_child, r, key,
                  add + 1 + cnt(t->left_child));
            l = t;
        }
        update_cnt(t);
    }
 
    void insert(treap_node_ptr& t, int pos, int v) {
        treap_node_ptr t1, t2;
        split(t, t1, t2, pos - 1);
        merge(t1, t1, new treap_node(v));
        merge(t, t1, t2);
    }
 
    void erase(treap_node_ptr& t, int pos) {
        treap_node_ptr t1, t2, t3;
        split(t, t1, t2, pos - 1);
        split(t2, t2, t3, 1);
        merge(t, t1, t3);
    }
 
    void reverse(treap_node_ptr t, int l, int r) {
        treap_node_ptr t1, t2, t3;
        split(t, t1, t2, l - 1);  // one-indexed
        split(t2, t2, t3, r - l + 1);
        t2->is_reversed ^= true;
        merge(t, t1, t2);
        merge(t, t, t3);
    }
 
    void inorder_traversal(treap_node_ptr t, std::vector<int>& a) {
        if (!t) return;
        push(t);
        inorder_traversal(t->left_child, a);
        a.push_back(t->value);
        inorder_traversal(t->right_child, a);
    }
 
    void print_treap(treap_node_ptr t) {
        std::vector<int> v;
        inorder_traversal(t, v);
        for (auto x : v) std::cerr << x << ' ';
        std::cerr << '\n';
    }
 
}  // namespace treap
 
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
        ll n, k;
        cin >> n >> k;
        vector pos(n + 1, -1);
        for (ll i = n; i >= 1; --i) {
            if (k >= i - 1) {
                pos[i] = 1;
                k -= i - 1;
            } else {
                pos[i] = int(i - k);
                k = 0;
            }
        }
        // now add in reverse order
        treap::treap_node_ptr root = nullptr;
        for (int i = 1; i <= n; ++i) treap::insert(root, pos[i], i);
        vector<int> permutation;
        treap::inorder_traversal(root, permutation);
        for (auto x : permutation) cout << x << ' ';
        cout << '\n';
    }
}

