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

int main() {
    IOinit();

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // we can construct the sorted list of all elements in the original array
    // back from this let's write out the corresponding strings in order let
    // f[i] be the string whose last element is the ith element in the original
    // array (suppose we know the indices of f[0..i] beforehand) to find the ith
    // element of the string s, look at the index of last element of f[i] if we
    // find the element at this index in the list of indices of s sorted
    // according to the values at those positions in s, then we are basically
    // finding the next element in the original string (because in the original
    // string, the element after the last element in f[i] is actually the first
    // element)

    string s;
    read_str(s);
    int n = s.size();
    vector<int> nextPosition;
    vector<vector<int>> positions(27);

    for (int i = 0; i < n; ++i) positions[max(0, s[i] - 'a' + 1)].push_back(i);

    for (int i = 0; i < 27; ++i)
        for (auto position : positions[i]) nextPosition.push_back(position);

    int position = -1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '#') {
            position = i;
            break;
        }
    }

    assert(~position);

    for (int i = 1; i < n; ++i) {
        position = nextPosition[position];
        write_char(s[position]);
    }

    write_char('\n');

    return 0;
}
