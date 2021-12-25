#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
 
#include <bits/stdc++.h>
 
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
 
using ll = int64_t;
 
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
 
struct Random : std::mt19937 {
    using std::mt19937::mt19937;
    using std::mt19937::operator();
    static int64_t gen_seed() {
        return std::chrono::steady_clock::now().time_since_epoch().count();
    }
    Random() : std::mt19937(gen_seed()) {}
    template <class Int>
    auto operator()(Int a, Int b)
        -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        return std::uniform_int_distribution<Int>(a, b)(*this);
    }
    template <class Int>
    auto operator()(Int a) -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        return std::uniform_int_distribution<Int>(0, a - 1)(*this);
    }
    template <class Real>
    auto operator()(Real a, Real b)
        -> std::enable_if_t<std::is_floating_point_v<Real>, Real> {
        return std::uniform_real_distribution<Real>(a, b)(*this);
    }
};
 
template <bool ToShuffle = false>
struct bipartite_matching {
    int n_left, n_right, flow = 0;
    std::vector<std::vector<int>> g;
    std::vector<int> match_from_left, match_from_right;
 
    bipartite_matching(int _n_left, int _n_right)
        : n_left(_n_left),
          n_right(_n_right),
          g(_n_left),
          match_from_left(_n_left, -1),
          match_from_right(_n_right, -1),
          dist(_n_left) {}
 
    void add(int u, int v) { g[u].push_back(v); }
 
    std::vector<int> dist;
 
    void bfs() {
        std::queue<int> q;
        for (int u = 0; u < n_left; ++u) {
            if (!~match_from_left[u])
                q.push(u), dist[u] = 0;
            else
                dist[u] = -1;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u])
                if (~match_from_right[v] && !~dist[match_from_right[v]]) {
                    dist[match_from_right[v]] = dist[u] + 1;
                    q.push(match_from_right[v]);
                }
        }
    }
 
    bool dfs(int u) {
        for (auto v : g[u])
            if (!~match_from_right[v]) {
                match_from_left[u] = v, match_from_right[v] = u;
                return true;
            }
        for (auto v : g[u])
            if (dist[match_from_right[v]] == dist[u] + 1 &&
                dfs(match_from_right[v])) {
                match_from_left[u] = v, match_from_right[v] = u;
                return true;
            }
        return false;
    }
 
    int get_max_matching() {
        if constexpr (ToShuffle) {
            Random rng;
            for (int i = 0; i < n_left; ++i)
                std::random_shuffle(std::begin(g[i]), std::end(g[i]), rng);
        }
        while (true) {
            bfs();
            int augment = 0;
            for (int u = 0; u < n_left; ++u)
                if (!~match_from_left[u]) augment += dfs(u);
            if (!augment) break;
            flow += augment;
        }
        return flow;
    }
 
    std::pair<std::vector<int>, std::vector<int>> minimum_vertex_cover() {
        std::vector<int> L, R;
        for (int u = 0; u < n_left; ++u) {
            if (!~dist[u])
                L.push_back(u);
            else if (~match_from_left[u])
                R.push_back(match_from_left[u]);
        }
        return {L, R};
    }
 
    std::vector<std::pair<int, int>> get_edges() {
        std::vector<std::pair<int, int>> ans;
        for (int u = 0; u < n_left; ++u)
            if (match_from_left[u] != -1)
                ans.emplace_back(u, match_from_left[u]);
        return ans;
    }
};
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> g(n);
        for (int i = 1, u, v; i != n; ++i) {
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<int> col(n, -1);
        const auto dfs = [&g, &col](const auto& self, int u, int p,
                                    int c) -> void {
            col[u] = c;
            for (auto v : g[u]) {
                if (v == p) continue;
                self(self, v, u, c ^ 1);
            }
        };
        dfs(dfs, 0, -1, 0);
        vector<int> l, r;
        vector<int> id(n);
        for (int i = 0; i < n; ++i)
            if (col[i])
                l.push_back(i), id[i] = l.size() - 1;
            else
                r.push_back(i), id[i] = r.size() - 1;
        bipartite_matching<true> b(l.size(), r.size());
        for (int i = 0; i < n; ++i)
            if (col[i])
                for (auto x : g[i]) b.add(id[i], id[x]);
        cout << b.get_max_matching() << '\n';
    }
    return 0;
}
