#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

struct node {
    int left;
    int right;
    int max;
    int tot;
    int8_t leftel;
    int8_t rightel;
    bool isfull;
    node()
        : left(0),
          right(0),
          max(0),
          tot(0),
          leftel(0),
          rightel(0),
          isfull(true){};
    node(int el)
        : left(1),
          right(1),
          max(1),
          tot(1),
          leftel(el),
          rightel(el),
          isfull(true){};
};

node combine(node a, node b) {
    if (a.tot == 0) return b;
    if (b.tot == 0) return a;
    node n;
    n.tot = a.tot + b.tot;
    n.left = a.left;
    n.right = b.right;
    n.max = max(a.max, b.max);
    if (a.rightel == b.leftel) {
        n.max = max(n.max, a.right + b.left);
        if (a.isfull) n.left += b.left;
        if (b.isfull) n.right += a.right;
    }
    n.leftel = a.leftel;
    n.rightel = b.rightel;
    n.isfull = n.left == n.tot;
    return n;
}

static const node ID;

node t[4 * maxn];

void build(string &s, int v, int l, int r) {
    if (l == r) {
        t[v] = node(s[l] - '0');
    } else {
        int mid = (l + r) >> 1;
        build(s, v << 1, l, mid);
        build(s, (v << 1) | 1, mid + 1, r);
        t[v] = combine(t[v << 1], t[(v << 1) | 1]);
    }
}

void update(int v, int l, int r, int i, int val) {
    if (l > r) {
        return;
    } else if (l == r) {
        t[v] = node(val);
    } else {
        int mid = (l + r) >> 1;
        if (i <= mid)
            update(v << 1, l, mid, i, val);
        else
            update((v << 1) | 1, mid + 1, r, i, val);
        t[v] = combine(t[v << 1], t[(v << 1) | 1]);
    }
}

node query(int v, int tl, int tr, int l, int r) {
    if (l > r) {
        return ID;
    } else if (l == tl && r == tr) {
        return t[v];
    } else {
        int tm = (tl + tr) >> 1;
        return combine(query(v << 1, tl, tm, l, min(r, tm)),
                       query((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r));
    }
}

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

int main() {
    IOinit();

    int n, m, x;
    string s;
    read_str(s);
    read_int(m);
    n = s.size();

    build(s, 1, 0, n - 1);

    for (int i = 0; i < m; ++i) {
        read_int(x);
        --x;
        if (s[x] == '0')
            s[x] = '1';
        else
            s[x] = '0';
        update(1, 0, n - 1, x, s[x] - '0');
        node nd = query(1, 0, n - 1, 0, n - 1);
        write_int(nd.max, ' ');
    }
    write_char('\n');

    return 0;
}
