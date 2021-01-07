#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

template <int32_t MOD = 998'244'353>
struct Modular {
    int32_t value;
    static const int32_t MOD_value = MOD;

    Modular(long long v = 0) {
        value = v % MOD;
        if (value < 0) value += MOD;
    }
    Modular(long long a, long long b) : value(0) {
        *this += a;
        *this /= b;
    }

    Modular& operator+=(Modular const& b) {
        value += b.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }
    Modular& operator-=(Modular const& b) {
        value -= b.value;
        if (value < 0) value += MOD;
        return *this;
    }
    Modular& operator*=(Modular const& b) {
        value = (long long)value * b.value % MOD;
        return *this;
    }

    friend Modular mexp(Modular a, long long e) {
        Modular res = 1;
        while (e) {
            if (e & 1) res *= a;
            a *= a;
            e >>= 1;
        }
        return res;
    }

    friend Modular inverse(Modular a) { return mexp(a, MOD - 2); }
    Modular& operator/=(Modular const& b) { return *this *= inverse(b); }
    friend Modular operator+(Modular a, Modular const b) { return a += b; }
    friend Modular operator-(Modular a, Modular const b) { return a -= b; }
    friend Modular operator-(Modular const a) { return 0 - a; }
    friend Modular operator*(Modular a, Modular const b) { return a *= b; }
    friend Modular operator/(Modular a, Modular const b) { return a /= b; }
    friend std::ostream& operator<<(std::ostream& os, Modular const& a) {
        return os << a.value;
    }
    friend bool operator==(Modular const& a, Modular const& b) {
        return a.value == b.value;
    }
    friend bool operator<(Modular const& a, Modular const& b) {
        return a.value < b.value;
    }
    friend bool operator!=(Modular const& a, Modular const& b) {
        return a.value != b.value;
    }
};

using mint = Modular<mod>;

// datatype of nodes of segment tree
typedef mint T;
// datatype of vector that's generating the segment tree
typedef mint S;
T unit = 0;

struct SegTree {
    // node of segment tree from a value
    T make_node(S val) { return val; }
    // combine function - needs to be an associative function
    T combine(T a, T b) { return a + b; }
    // point update function - updating the element in the array
    void update_val(T& a, S b) { a += b; }

    vector<T> t;
    int32_t n;

    SegTree(int32_t n = 0, T def = unit) : t(n << 1, def), n(n) {}
    SegTree(vector<S>& a, T def = unit) {
        n = a.size();
        t.assign(n << 1, unit);
        for (int32_t i = 0; i < n; ++i) {
            t[i + n] = make_node(a[i]);
        }
        for (int32_t i = n - 1; i; --i) {
            t[i] = combine(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int32_t pos, S val) {
        for (update_val(t[pos += n], val); pos >>= 1;) {
            t[pos] = combine(t[pos << 1], t[pos << 1 | 1]);
        }
    }

    T query(int32_t l, int32_t r) {
        T ra = unit, rb = unit;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ra = combine(ra, t[l++]);
            if (r & 1) rb = combine(t[--r], rb);
        }
        return combine(ra, rb);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << setprecision(10) << fixed;

    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> rank(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<pair<int, int>> b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = {a[i], i};
    }
    sort(b.begin(), b.end());

    vector<int> m(n);
    int currank = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || b[i].first != b[i - 1].first) currank++;
        m[b[i].second] = currank;
    }

    vector<mint> dp(n);

    SegTree st(n);
    mint ans = 0;

    vector<mint> curarray(n);

    for (int i = n - 1; ~i; --i) {
        int rnk = m[i];
        dp[i] = 1 + st.query(rnk, n);
        ans += dp[i];
        st.update(rnk - 1, dp[i]);
    }

    cout << ans << endl;

    return 0;
}
