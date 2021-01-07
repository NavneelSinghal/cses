#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

namespace IO {
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

    for (int i = 0; i < 100; i++) lookup[i] = uint8_t((i / 10 << 4) + i % 10);
}
}  // namespace IO

using namespace IO;

struct node {
    int hash1, hash2;
    int size;  // of the hash length, not the subtree size
    node() : hash1(0), hash2(0), size(0){};
    node(int h1, int h2, int sz) : hash1(h1), hash2(h2), size(sz){};
    bool operator==(node &n) {
        return hash1 == n.hash1 && hash2 == n.hash2 && size == n.size;
    }
    bool operator<(node &n) {
        if (hash1 != n.hash2) return hash1 < n.hash1;
        return hash2 < n.hash2;
    }
};

static const int mod1 = 1e9 + 7;
static const int mod2 = 1e9 + 9;

int pwr(int a, long long n, int mod) {
    assert(n >= 0);
    long long res = 1;
    while (n) {
        if (n & 1) res = (res * a) % mod;
        if (n >>= 1) a = (a * a) % mod;
    }
    return res;
}

int main() {
    IOinit();

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    read_int(t);
    // cin >> t;
    while (t--) {
        int n;
        read_int(n);
        vector<vector<int>> g[2];
        for (int i = 0; i < 2; ++i) {
            g[i].resize(n);
            int u, v;
            for (int j = 1; j < n; ++j) {
                // cin >> u >> v;
                read_int(u, v);
                --u, --v;
                g[i][u].push_back(v);
                g[i][v].push_back(u);
            }
        }
        node hashes[2];
        for (int i = 0; i < 2; ++i) {
            vector<bool> visited(n);
            function<node(int)> dfs = [&](int v) {
                int h1 = 0;
                int h2 = 0;
                vector<node> vec;
                visited[v] = true;
                for (auto u : g[i][v]) {
                    if (visited[u]) continue;
                    vec.push_back(dfs(u));
                }
                sort(vec.begin(), vec.end());
                int pw = 0;
                int n = vec.size();
                for (int i = 0; i < n; ++i) {
                    pw++;
                    h1 += ((long long)pwr(3, pw, mod1) * vec[i].hash1) % mod1;
                    h2 += ((long long)pwr(2, pw, mod2) * vec[i].hash2) % mod2;
                    if (h1 >= mod1) h1 -= mod1;
                    if (h2 >= mod2) h2 -= mod2;
                    pw += vec[i].size;
                }
                pw++;
                h1 += pwr(3, pw, mod1);
                if (h1 >= mod1) h1 -= mod1;
                h2 += pwr(2, pw, mod2);
                if (h2 >= mod2) h1 -= mod2;
                return node(h1, h2, pw);
            };
            hashes[i] = dfs(0);
        }
        if (hashes[0] == hashes[1]) {
            write_str("YES\n");
        } else {
            write_str("NO\n");
        }
    }

    return 0;
}
