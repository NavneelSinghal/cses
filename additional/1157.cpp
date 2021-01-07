#include <iostream>
int x, y;
int main() {
    std::cin >> x >> y;
    --x ^= --y;
    std::cout << x;
}
