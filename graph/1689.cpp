#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/stdc++.h"
#ifdef DEBUG
    #include "includes/debug/debug.hpp"
#else
    #define debug(...) 0
#endif

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

using namespace std;

template <class T, class D = void>
struct bigger_type {};
template <class T>
struct bigger_type<T, std::enable_if_t<sizeof(T) <= 4, void>> {
    using type = std::uint64_t;
};
template <class T>
struct bigger_type<T, std::enable_if_t<4 < sizeof(T) && sizeof(T) <= 8, void>> {
    using type = __uint128_t;
};

template <class RNG>
struct Random : RNG {
    using RNG::operator();
    Random() : RNG(gen_seed()) {}

    static std::uint64_t gen_seed() {
        return std::chrono::steady_clock::now().time_since_epoch().count();
    }

    using T = typename RNG::result_type;
    using U = typename bigger_type<T>::type;
    static constexpr std::size_t shift_size = CHAR_BIT * sizeof(T);

    // generate random integer in [0, N]
    auto generate_random_n(const T N) {
        U product = static_cast<U>(operator()() - RNG::min()) * N;
        T lsb = static_cast<T>(product);
        if (lsb < N) {
            T threshold = -static_cast<T>(N) % static_cast<T>(N);
            while (lsb < threshold) {
                product = static_cast<U>(operator()() - RNG::min()) * N;
                lsb = static_cast<T>(product);
            }
        }
        return static_cast<T>(product >> shift_size);
    }
    template <class Int>
    auto operator()(Int a, Int b)
        -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        // return a + static_cast<Int>(generate_random_n(b - a));
        return std::uniform_int_distribution<Int>(a, b)(*this);
    }
    template <class Int>
    auto operator()(Int a) -> std::enable_if_t<std::is_integral_v<Int>, Int> {
        // return static_cast<Int>(generate_random_n(a - 1));
        return std::uniform_int_distribution<Int>(0, a - 1)(*this);
    }
    template <class Real>
    auto operator()(Real a, Real b)
        -> std::enable_if_t<std::is_floating_point_v<Real>, Real> {
        return std::uniform_real_distribution<Real>(a, b)(*this);
    }
};

using RandomMersenne32 = Random<std::mt19937>;
using RandomMersenne64 = Random<std::mt19937_64>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";

        RandomMersenne32 rng;

        // Warnsdorff's heuristic
        static constexpr array<pair<int, int>, 8> moves = {
            pair{1, 2}, pair{-1, 2}, pair{1, -2}, pair{-1, -2},
            pair{2, 1}, pair{2, -1}, pair{-2, 1}, pair{-2, -1}};

        static constexpr int N = 8;
        static constexpr int M = 8;

        array<array<int, M>, N> board{};

        auto valid = [&](int i, int j) {
            return 0 <= i && i < N && 0 <= j && j < M && board[i][j] == 0;
        };
        auto get_rank = [&](int i, int j) {
            int ans = 0;
            for (auto [dx, dy] : moves) ans += valid(i + dx, j + dy);
            return ans;
        };
        auto get_rank_array = [&](int x, int y) {
            array<int, 8> rank_array;
            for (int i = 0; i < 8; ++i) {
                auto [dx, dy] = moves[i];
                int ii = x + dx;
                int jj = y + dy;
                if (valid(ii, jj))
                    rank_array[i] = get_rank(ii, jj);
                else
                    rank_array[i] = 9;
            }
            return rank_array;
        };

        auto solve = [&](int start_x, int start_y) {
            while (true) {
                bool works = true;
                for (int i = 0; i < N; ++i) board[i].fill(0);
                board[start_x][start_y] = 1;
                array<int, 8> rank_array;
                int cur_x = start_x, cur_y = start_y;
                int visited = 1;
                array<int, 8> positions;
                while (visited != N * M) {
                    rank_array = get_rank_array(cur_x, cur_y);
                    auto it = min_element(begin(rank_array), end(rank_array));
                    if (*it == 9) {
                        works = false;
                        break;
                    }
                    int cnt = 0;
                    for (int i = 0; i < 8; ++i)
                        if (rank_array[i] == *it) positions[cnt++] = i;
                    cnt = rng(cnt);
                    auto [dx, dy] = moves[positions[cnt]];
                    cur_x += dx, cur_y += dy;
                    board[cur_x][cur_y] = ++visited;
                }
                if (works) break;
            }
        };

        int x, y;
        cin >> x >> y;
        solve(y - 1, x - 1);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) cout << board[i][j] << ' ';
            cout << '\n';
        }
    }
}

