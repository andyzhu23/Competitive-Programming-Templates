#include <vector>
#include <algorithm>
namespace cp {
#ifndef CP_LAZY_MIN_SEGTREE
#define CP_LAZY_MIN_SEGTREE
template <typename T> class lazy_min_segtree {
    static constexpr int lc(int rt) { return rt << 1; }
    static constexpr int rc(int rt) { return rt << 1 | 1; }

    void push_up(int rt) {
        st[rt] = std::min(st[lc(rt)], st[rc(rt)]);
    }
    void push_down(int rt) {
        if(lazy[rt] != 0) {
            st[lc(rt)] += lazy[rt];
            st[rc(rt)] += lazy[rt];
            lazy[lc(rt)] += lazy[rt];
            lazy[rc(rt)] += lazy[rt];
            lazy[rt] = 0;
        }
    }
    void build(int rt, int l, int r, const std::vector<T>& a) {
        if(l == r) { st[rt] = a[l - 1]; return; }
        int mid = (l + r) >> 1;
        build(lc(rt), l, mid, a);
        build(rc(rt), mid + 1, r, a);
        push_up(rt);
    }
    void upd(int rt, int l, int r, int x, int y, T val) {
        if(l == x && y == r) { st[rt] += val; lazy[rt] += val; return; }
        int mid = (l + r) >> 1;
        push_down(rt);
        if(y <= mid) upd(lc(rt), l, mid, x, y, val);
        else if(x > mid) upd(rc(rt), mid + 1, r, x, y, val);
        else upd(lc(rt), l, mid, x, mid, val), upd(rc(rt), mid + 1, r, mid + 1, y, val);
        push_up(rt);
    }
    T query(int rt, int l, int r, int x, int y) {
        if(l == x && y == r) return st[rt];
        int mid = (l + r) >> 1;
        push_down(rt);
        if(y <= mid) return query(lc(rt), l, mid, x, y);
        else if(x > mid) return query(rc(rt), mid + 1, r, x, y);
        else return std::min(query(lc(rt), l, mid, x, mid), query(rc(rt), mid + 1, r, mid + 1, y));
    }

public:
    lazy_min_segtree(int n) : n(n), st((n << 2) + 5), lazy((n << 2) + 5) {}
    lazy_min_segtree(const std::vector<T>& a) : n((int)a.size()), st((n << 2) + 5), lazy((n << 2) + 5) {
        build(1, 1, n, a);
    }
    void upd(int pos, T val) { upd(1, 1, n, pos, pos, val); }
    void upd(int x, int y, T val) { upd(1, 1, n, x, y, val); }
    T query(int x, int y) { return query(1, 1, n, x, y); }

private:
    int n;
    std::vector<T> st, lazy;
};

#endif // CP_LAZY_MIN_SEGTREE
} // namespace cp
