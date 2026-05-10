#include <vector>
namespace cp {
#ifndef CP_SEGTREE
#define CP_SEGTREE
template <typename T> class segtree {
    static constexpr int lc(int rt) { return rt << 1; }
    static constexpr int rc(int rt) { return rt << 1 | 1; }
    static T op(T a, T b) { return a + b; } // edit op() to change the combine

    void push_up(int rt) {
        st[rt] = op(st[lc(rt)], st[rc(rt)]);
    }
    void build(int rt, int l, int r, const std::vector<T>& a) {
        if(l == r) { st[rt] = a[l - 1]; return; }
        int mid = (l + r) >> 1;
        build(lc(rt), l, mid, a);
        build(rc(rt), mid + 1, r, a);
        push_up(rt);
    }
    void upd(int rt, int l, int r, int pos, T val) {
        if(l == r) { st[rt] = val; return; }
        int mid = (l + r) >> 1;
        if(pos <= mid) upd(lc(rt), l, mid, pos, val);
        else upd(rc(rt), mid + 1, r, pos, val);
        push_up(rt);
    }
    T query(int rt, int l, int r, int x, int y) const {
        if(l == x && y == r) return st[rt];
        int mid = (l + r) >> 1;
        if(y <= mid) return query(lc(rt), l, mid, x, y);
        else if(x > mid) return query(rc(rt), mid + 1, r, x, y);
        else return op(query(lc(rt), l, mid, x, mid), query(rc(rt), mid + 1, r, mid + 1, y));
    }

public:
    segtree(int n) : n(n), st((n << 2) + 5) {}
    segtree(const std::vector<T>& a) : n((int)a.size()), st((n << 2) + 5) {
        build(1, 1, n, a);
    }
    void upd(int pos, T val) { upd(1, 1, n, pos, val); }
    T query(int x, int y) const { return query(1, 1, n, x, y); }

private:
    int n;
    std::vector<T> st;
};

#endif // CP_SEGTREE
} // namespace cp
