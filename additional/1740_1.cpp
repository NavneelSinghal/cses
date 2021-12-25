 combine(d[r], sm);
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
 
    void update(int k) { d[k] = combine(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, Update f) {
        d[k] = apply_update(f, d[k]);
        if constexpr (is_lazy)
            if (k < size) lz[k] = compose_updates(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id_update;
    }
};
// clang-format on
 
template <class T>
auto compress(const vector<T>& a) {
    int n = size(a);
    vector<pair<T, int>> p(n);
    for (int i = 0; i < n; ++i) p[i] = {a[i], i};
    sort(begin(p), end(p));
    vector<int> compressed(n);
    vector<T> vals;
    for (int k = 0, rnk = -1; k < n; ++k) {
        if (k == 0 or p[k - 1].first < p[k].first)
            vals.push_back(p[k].first), ++rnk;
        compressed[p[k].second] = rnk;
    }
    return make_pair(compressed, vals);
}
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n;
        cin >> n;
        vector<int> pos;
        pos.reserve(4 * n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 4; ++j) {
                int y;
                cin >> y;
                pos.push_back(y);
            }
        }
        auto [compressed, vals] = compress(pos);
        struct event {
            int type;
            int x;
            int y, Y;
            bool operator<(const event& other) { return x < other.x; }
            event() {}
            event(int _type, int _x, int _y, int _Y)
                : type(_type), x(_x), y(_y), Y(_Y) {}
        };
        vector<event> events;
        for (int i = 0; i < 4 * n; i += 4) {
            auto [x1, y1, x2, y2] = tie(compressed[i], compressed[i + 1],
                                        compressed[i + 2], compressed[i + 3]);
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            if (x1 == x2)
                events.emplace_back(-1, x1, y1, y2);
            else
                events.emplace_back(0, x1, y1, -1),
                    events.emplace_back(1, x2, y1, -1);
        }
        sort(begin(events), end(events));
 
        using Base = ll;
        using Node = ll;
        using Update = int;
        const Node id_node = 0;
        const Update id_update = 0;
        auto make_node = [](auto x, auto) {
            return x;
        };
        auto combine = [](auto a, auto b) {
            return a + b;
        };
        auto apply_update = [](auto a, auto b) {
            return a + b;
        };
        lazy_segtree st(vector<Base>(vals.size() + 1), id_node, make_node,
                        combine, id_update, apply_update);
 
        ll ans = 0;
        for (auto [type, x, y, Y] : events) {
            if (type == 0) {
                st.update(y, 1);
            } else if (type == 1) {
                st.update(y, -1);
            } else {
                ans += st.query(y, Y + 1);
            }
        }
        cout << ans << '\n';
    }
}
