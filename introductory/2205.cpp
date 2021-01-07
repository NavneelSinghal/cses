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

int main() {
    IOinit();

    int n;
    read_int(n);

    const int s = 1 << n;
    char a[s][n + 1];

    a[0][0] = '0';
    a[1][0] = '1';

    for (int i = 0; i < s; ++i) a[i][n] = '\0';

    for (int i = 2, p = 1; i < (1 << n); p++, i <<= 1) {
        for (int j = 0, k = (i << 1) - 1; j < i; ++j, --k) {
            copy(a[j], a[j] + p, a[k]);
            a[k][p] = '1';
            a[j][p] = '0';
        }
    }

    for (int i = 0; i < s; ++i) {
        write_str(a[i], ' ');
    }

    write_char('\n');

    return 0;
}
