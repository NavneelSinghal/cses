#ifndef LOCAL
    #pragma GCC optimize("O3,unroll-loops")
//    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
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
 
#define all(a) begin(a), end(a)
template <int maxn>
struct FFT {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    typedef complex<double> cpx;
    int rev[MAXN];
    cpx rt[MAXN];
    FFT() {
        rt[1] = cpx{1, 0};
        for (int k = 2; k < MAXN; k *= 2) {
            cpx z[] = {1, polar(1.0, M_PI / k)};
            for (int i = k; i < 2 * k; i++) rt[i] = rt[i / 2] * z[i & 1];
        }
    }
    void fft(cpx* a, int n) {
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << lg2(n)) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];
                    cpx z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
    }
 
    cpx in[MAXN], out[MAXN];
    vector<double> multiply(const vector<double>& a, const vector<double>& b) {
        fill(all(in), cpx{0, 0}), fill(all(out), cpx{0, 0});
        if (a.empty() || b.empty()) return {};
        int sz = a.size() + b.size() - 1, n = 1 << lg2(sz);
        vector<double> res(sz);
        copy(all(a), begin(in));
        for (int i = 0; i < b.size(); i++) in[i].imag(b[i]);
        fft(in, n);
        for (int i = 0; i < n; i++) in[i] *= in[i];
        for (int i = 0; i < n; i++)
            out[i] = in[(n - i) & (n - 1)] - conj(in[i]);
        fft(out, n);
        for (int i = 0; i < sz; i++) res[i] = out[i].imag() / (4 * n);
        return res;
    }
};
 
FFT<800'000> fft;
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        string s;
        cin >> s;
        int n = (int)s.size();
        vector<ll> a(n + 1);
        for (int i = 0; i < n; ++i) a[i + 1] = a[i] + s[i] - '0';
        vector<double> cnt(n + 1), cnt_rev(n + 1);
        for (int i = 0; i <= n; ++i) cnt[a[i]] += 1, cnt_rev[n - a[i]] += 1;
        auto prod = fft.multiply(cnt, cnt_rev);
        cout << (ll(roundl(prod[n])) - (n + 1)) / 2 << ' ';
        for (int i = n + 1; i < 2 * n + 1; ++i)
            cout << ll(roundl(prod[i])) << ' ';
        cout << '\n';
    }
}
 
