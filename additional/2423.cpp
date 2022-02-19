#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC target("avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, m;
        cin >> n >> m;
        if (!(n % 2 == 0 && m % 3 == 0) && !(n % 3 == 0 && m % 2 == 0)) {
            if (n % 6 != 0 && m % 6 != 0) {
                if (n % 3 != 0 && m % 3 != 0) {
                    cout << "NO\n";
                } else {
                    // at least one of these is divisible by 3
                    // none of these is divisible by 2, since otherwise
                    // divisible by 6
                    assert(m % 2 != 0);
                    assert(n % 2 != 0);
                    if (n % 3 == 0 && m % 3 == 0 && min(n, m) <= 3) {
                        cout << "NO\n";
                    } else {
                        bool transpose = false;
                        if (m % 3 == 0) {
                            swap(n, m);
                            transpose = true;
                        }
                        assert(n % 3 == 0);
                        if (n < 9) {
                            cout << "NO\n";
                        } else {
                            // m = 1, 3, 5, 7, 9, 10, 11, 12, 13
                            if (m < 5) {
                                cout << "NO\n";
                            } else {
                                cout << "YES\n";
                                vector<string> grid(n, string(m, '0'));
                                // m is odd
                                vector<string> figure_9_5 = {
                                    "GGQQV", "GMQVV", "IMMXX", "IITTX", "FFTUU",
                                    "GFQQU", "GGQWW", "IINXW", "INNXX"};
                                vector<string> figure_6_5 = {"GGQQV", "GMQVV",
                                                             "IMMXX", "IITTX",
                                                             "FFKTU", "FKKUU"};

                                for (int i = 0; i < n; ++i) {
                                    for (int j = 0; j < m - 5; ++j) {
                                        int offset = 0;
                                        if ((i / 3) % 2 == (j / 2) % 2) {
                                            offset += 2;
                                        }
                                        if (i % 3 == 0) {
                                            grid[i][j] = 'A' + offset;
                                        } else if (i % 3 == 1) {
                                            grid[i][j] = 'A' + offset + (j % 2);
                                        } else {
                                            grid[i][j] = 'B' + offset;
                                        }
                                    }
                                }

                                assert((n - 9) % 6 == 0);
                                for (int i = 0; i < n - 9; ++i) {
                                    for (int j = 0; j < 5; ++j) {
                                        grid[i][m - 5 + j] =
                                            figure_6_5[i % 6][j];
                                    }
                                }

                                for (int i = n - 9; i < n; ++i) {
                                    for (int j = 0; j < 5; ++j) {
                                        grid[i][m - 5 + j] =
                                            figure_9_5[(i - n + 9) % 9][j];
                                    }
                                }

                                if (transpose) {
                                    for (int j = 0; j < m; ++j) {
                                        for (int i = 0; i < n; ++i) {
                                            cout << grid[i][j];
                                        }
                                        cout << '\n';
                                    }
                                } else {
                                    for (int i = 0; i < n; ++i) {
                                        for (int j = 0; j < m; ++j) {
                                            cout << grid[i][j];
                                        }
                                        cout << '\n';
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                bool transpose = false;
                if (m % 6 == 0) {
                    swap(n, m);
                    transpose = true;
                }
                assert(n % 6 == 0);
                assert(m % 2 != 0 && m % 3 != 0);
                if (m == 1) {
                    cout << "NO\n";
                } else {
                    cout << "YES\n";
                    assert(m >= 5);
                    assert(m % 2 != 0);
                    // m >= 5
                    vector<string> grid(n, string(m, '0'));

                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < m - 5; ++j) {
                            int offset = 0;
                            if ((i / 3) % 2 == (j / 2) % 2) {
                                offset += 2;
                            }
                            if (i % 3 == 0) {
                                grid[i][j] = 'A' + offset;
                            } else if (i % 3 == 1) {
                                grid[i][j] = 'A' + offset + (j % 2);
                            } else {
                                grid[i][j] = 'B' + offset;
                            }
                        }
                    }

                    vector<string> figure = {
                        "GGIIFF", "GMMIFK", "QQMTKK", "QVXTTU", "VVXXUU",
                    };

                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < 5; ++j) {
                            grid[i][m - 5 + j] = figure[j][i % 6];
                        }
                    }

                    if (transpose) {
                        for (int j = 0; j < m; ++j) {
                            for (int i = 0; i < n; ++i) {
                                cout << grid[i][j];
                            }
                            cout << '\n';
                        }
                    } else {
                        for (int i = 0; i < n; ++i) {
                            for (int j = 0; j < m; ++j) {
                                cout << grid[i][j];
                            }
                            cout << '\n';
                        }
                    }
                }
            }
        } else {
            cout << "YES\n";
            bool transpose = false;
            if (n % 2 == 0 && m % 3 == 0) {
                transpose = true;
                swap(n, m);
            }

            // vertical

            vector<string> grid(n, string(m, '0'));

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    int offset = 0;
                    if ((i / 3) % 2 == (j / 2) % 2) {
                        offset += 2;
                    }
                    if (i % 3 == 0) {
                        grid[i][j] = 'A' + offset;
                    } else if (i % 3 == 1) {
                        grid[i][j] = 'A' + offset + (j % 2);
                    } else {
                        grid[i][j] = 'B' + offset;
                    }
                }
            }

            if (transpose) {
                for (int j = 0; j < m; ++j) {
                    for (int i = 0; i < n; ++i) {
                        cout << grid[i][j];
                    }
                    cout << '\n';
                }
            } else {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        cout << grid[i][j];
                    }
                    cout << '\n';
                }
            }
        }
    }
}

