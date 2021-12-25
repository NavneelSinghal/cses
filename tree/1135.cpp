#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
 
#include <bits/stdc++.h>
 
using namespace std;
 
struct HLD_LCA {
    using graph = std::vector<std::vector<int>>;
    HLD_LCA(const graph &G, int root = 0)
        : N((int)G.size()),
          g(G),
          par(N),
          start(N),
          depth(N),
          sz(N),
          in_time(N) {
        par[root] = -1;
        timer = 0;
        dfs_sz(root);
        start[root] = root;
        dfs_hld(root);
    }
 
    bool is_anc(int u, int v) {
        return in_time[u] <= in_time[v] && in_time[u] + sz[u] >= in_time[v];
    }
 
    void dfs_sz(int u) {
        sz[u] = 1;
        for (auto &v : g[u]) {
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
        for (auto &v : g[u]) {
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
 
    int N;
    graph g;
    std::vector<int> par, start, depth, sz, in_time;
    int timer;
};
namespace IO {
#define CUSTOM_IO
    using namespace std;
    const int BUFFER_SIZE = 1 << 15;
    char input_buffer[BUFFER_SIZE];
    size_t input_pos = 0, input_len = 0;
    char output_buffer[BUFFER_SIZE];
    int output_pos = 0;
    char number_buffer[100];
    uint8_t lookup[100];
 
    void _update_input_buffer() {
        input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
        input_pos = 0;
        if (input_len == 0) input_buffer[0] = EOF;
    }
 
    inline char next_char(bool advance = true) {
        if (input_pos >= input_len) _update_input_buffer();
        return input_buffer[advance ? input_pos++ : input_pos];
    }
 
    inline bool isspace(char c) {
        return (unsigned char)(c - '\t') < 5 || c == ' ';
    }
 
    inline void read_char(char &c) {
        while (isspace(next_char(false))) next_char();
        c = next_char();
    }
 
    template <typename T>
    inline void read_int(T &number) {
        bool negative = false;
        number = 0;
        while (!isdigit(next_char(false)))
            if (next_char() == '-') negative = true;
        do {
            number = 10 * number + (next_char() - '0');
        } while (isdigit(next_char(false)));
        if (negative) number = -number;
    }
 
    template <typename T, typename... Args>
    inline void read_int(T &number, Args &... args) {
        read_int(number);
        read_int(args...);
    }
 
    inline void read_str(string &str) {
        while (isspace(next_char(false))) next_char();
        str.clear();
        do {
            str += next_char();
        } while (!isspace(next_char(false)));
    }
 
    void _flush_output() {
        fwrite(output_buffer, sizeof(char), output_pos, stdout);
        output_pos = 0;
    }
 
    inline void write_char(char c) {
        if (output_pos == BUFFER_SIZE) _flush_output();
        output_buffer[output_pos++] = c;
    }
 
    template <typename T>
    inline void write_int(T number, char after = '\0') {
        if (number < 0) {
            write_char('-');
            number = -number;
        }
        int length = 0;
        while (number >= 10) {
            uint8_t lookup_value = lookup[number % 100];
            number /= 100;
            number_buffer[length++] = char((lookup_value & 15) + '0');
            number_buffer[length++] = char((lookup_value >> 4) + '0');
        }
        if (number != 0 || length == 0) write_char(char(number + '0'));
        for (int i = length - 1; i >= 0; i--) write_char(number_buffer[i]);
        if (after) write_char(after);
    }
 
    inline void write_str(const string &str, char after = '\0') {
        for (char c : str) write_char(c);
        if (after) write_char(after);
    }
 
    void IOinit() {
        // Make sure _flush_output() is called at the end of the program.
        bool exit_success = atexit(_flush_output) == 0;
        assert(exit_success);
        for (int i = 0; i < 100; i++)
            lookup[i] = uint8_t((i / 10 << 4) + i % 10);
    }
}  // namespace IO
 
using namespace IO;
 
int main() {
    // cin.tie(nullptr)->sync_with_stdio(false);
    IOinit();
    int t = 1;
 
    while (t--) {
        int n, q;
        read_int(n, q);
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u, v;
            read_int(u, v);
            --u, --v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
 
        HLD_LCA hld(g);
        vector<int> diff(n);
 
        while (q--) {
            int u, v;
            read_int(u, v);
            --u, --v;
            write_int(hld.dist(u, v), '\n');
        }
    }
}
