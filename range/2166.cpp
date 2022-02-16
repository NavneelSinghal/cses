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
 
// clang-format off
template <class Base,
          class Node,
          class Update,
          class MakeNode,
          class CombineNodes,
          class ApplyUpdate,
          class ComposeUpdates = std::nullptr_t,
          class CheckLazy = std::nullptr_t>
struct lazy_segtree {
    static constexpr bool is_lazy =
        !std::is_same<ComposeUpdates, std::nullptr_t>::value;
    static constexpr bool is_check_lazy = !std::is_same<CheckLazy, std::nullptr_t>::value;
 
   public:
    template <typename... T>
    explicit lazy_segtree(int n, const Base& id_base, T... args)
        : lazy_segtree(std::vector<Base>(n, id_base), args...) {}
    explicit lazy_segtree(const std::vector<Base>& v,
                          const Node& _id_node,
                          const MakeNode& _make_node,
                          const CombineNodes& _combine,
                          const Update& _id_update,
                          const ApplyUpdate& _apply_update,
                          const ComposeUpdates& _compose_updates = nullptr,
                          const CheckLazy& _check_lazy = nullptr)
        : _n(int(v.size())),
          make_node(_make_node),
          combine(_combine),
          id_node(_id_node),
          apply_update(_apply_update),
          id_update(_id_update),
          compose_updates(_compose_updates),
          check_lazy(_check_lazy) {
        build(v);
    }
 
    void build(const std::vector<Base>& v) {
        _n = int(v.size());
        log = 0;
        while ((1 << log) < _n) ++log;
        size = 1 << log;
        d = std::vector<Node>(2 * size, id_node);
        if constexpr (is_lazy) lz = std::vector<Update>(size, id_update);
        for (int i = 0; i < _n; i++) d[size + i] = make_node(v[i], i);
        for (int i = size - 1; i >= 1; i--) update(i);
    }
    
    void set(int p, Node x) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; ++i) update(p >> i);
    }
 
    Node get(int p) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
 
    Node query(int l, int r) {
        if (l == r) return id_node;
        l += size, r += size;
        if constexpr (is_lazy) {
            int l_ctz = __builtin_ctz(l);
            int r_ctz = __builtin_ctz(r);
            for (int i = log; i > l_ctz; --i) push(l >> i);
            for (int i = log; i > r_ctz; --i) push((r - 1) >> i);
        }
        Node sml = id_node, smr = id_node;
        while (l < r) {
            if (l & 1) sml = combine(sml, d[l++]);
            if (r & 1) smr = combine(d[--r], smr);
            l >>= 1, r >>= 1;
        }
        return combine(sml, smr);
    }
    
    Node all_query() const { return d[1]; }
    
    void update(int p, Update f) {
        p += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = apply_update(f, d[p]);
        for (int i = 1; i <= log; ++i) update(p >> i);
    }
    
    void update(int l, int r, Update f) {
        if (l == r) return;
        l += size, r += size;
        const int l_ctz = __builtin_ctz(l);
        const int r_ctz = __builtin_ctz(r);
        if constexpr (is_lazy) {
            for (int i = log; i > l_ctz; --i) push(l >> i);
            for (int i = log; i > r_ctz; --i) push((r - 1) >> i);
        }
        {
            const int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1, r >>= 1;
            }
            l = l2, r = r2;
        }
        for (int i = l_ctz + 1; i <= log; ++i) update(l >> i);
        for (int i = r_ctz + 1; i <= log; ++i) update((r - 1) >> i);
    }
 
    template <class G>
    int max_right(int l, G g) {
        // assert(0 <= l && l <= _n);
        // assert(g(id_node));
        if (l == _n) return _n;
        l += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push(l >> i);
        Node sm = id_node;
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(combine(sm, d[l]))) {
                while (l < size) {
                    if constexpr (is_lazy) push(l);
                    l = (2 * l);
                    if (g(combine(sm, d[l]))) {
                        sm = combine(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = combine(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }
 
    template <class G>
    int min_left(int r, G g) {
        // assert(0 <= r && r <= _n);
        // assert(g(id_node));
        if (r == 0) return 0;
        r += size;
        if constexpr (is_lazy)
            for (int i = log; i >= 1; i--) push((r - 1) >> i);
        Node sm = id_node;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(combine(d[r], sm))) {
                while (r < size) {
                    if constexpr (is_lazy) push(r);
                    r = (2 * r + 1);
                    if (g(combine(d[r], sm))) {
                        sm = combine(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = combine(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
 
   private:
    int _n, size, log;
    std::vector<Node> d;
    std::vector<Update> lz;
    MakeNode make_node;
    CombineNodes combine;
    Node id_node;
    ApplyUpdate apply_update;
    Update id_update;
    ComposeUpdates compose_updates;
    CheckLazy check_lazy;
 
    void update(int k) { d[k] = combine(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, Update f) {
        d[k] = apply_update(f, d[k]);
        if constexpr (is_lazy)
            if (k < size) lz[k] = compose_updates(f, lz[k]);
    }
    void push(int k) {
        if constexpr (is_check_lazy) {
            if (!check_lazy(lz[k])) return;
        }
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id_update;
    }
};
// clang-format on
 
/*
   lazy_segtree(const std::vector<Base>& v,
                const Node& _id_node,
                const MakeNode& _make_node,
                const CombineNodes& _combine,
                const Update& _id_update,
                const ApplyUpdate& _apply_update,
                const ComposeUpdates& _compose_updates = nullptr,
                const CheckLazy& _check_lazy = nullptr)
*/
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, q;
        cin >> n >> q;
        constexpr ll linf = 1e18L;
        using Base = ll;
        using Node = ll;
        vector<Base> a(n), p(n);
        for (auto& x : a) cin >> x;
        partial_sum(begin(a), end(a), begin(p));
        constexpr Node id_node = -linf;
        constexpr auto make_node = [](Base b, int) -> Node {
            return b;
        };
        auto combine = [](const Node& a, const Node& b) -> Node {
            return max(a, b);
        };
        using Update = ll;
        constexpr Update id_update = 0;
        constexpr auto apply_update = [](const Update& u,
                                         const Node& n) -> Node {
            return u + n;
        };
        constexpr auto compose_updates = [](const Update& u,
                                            const Update& v) -> Update {
            return u + v;
        };
        lazy_segtree st(p, id_node, make_node, combine, id_update, apply_update,
                        compose_updates);
        while (q--) {
            int t;
            cin >> t;
            if (t == 1) {
                int k, u;
                cin >> k >> u;
                --k;
                st.update(k, n, u - a[k]);
                a[k] = u;
            } else {
                int l, r;
                cin >> l >> r;
                --l;
                cout << max(ll(0),
                            st.query(l, r) - (l == 0 ? 0 : st.query(l - 1, l)))
                     << '\n';
            }
        }
    }
}

