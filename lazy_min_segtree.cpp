/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T> class lazy_min_segtree {
    const int inf = 0x3f3f3f3f;
    vector<T> st, lazy;
    int n;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    void push_up(int rt) {
        st[rt] = min(st[lc], st[rc]);
    }
    void push_down(int rt) {
        if(lazy[rt] != inf) {
            st[lc] = lazy[rt];
            st[rc] = lazy[rt];
            lazy[lc] = lazy[rt];
            lazy[rc] = lazy[rt];
            lazy[rt] = inf;
        }
    }
    void build(int rt, int l, int r, vector<int>& a) {
        if(l == r) {
            st[rt] = a[l - 1];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid, a);
        build(rc, mid + 1, r, a);
        push_up(rt);
    }
    void upd(int rt, int l, int r, int x, int y, T val) {
        if(l == x && y == r) {
            st[rt] = val;
            lazy[rt] = val;
            return;
        }
        int mid = (l + r) >> 1;
        push_down(rt);
        if(y <= mid) upd(lc, l, mid, x, y, val);
        else if(x > mid) upd(rc, mid + 1, r, x, y, val);
        else upd(lc, l, mid, x, mid, val), upd(rc, mid + 1, r, mid + 1, y, val);
        push_up(rt);
    }
    T query(int rt, int l, int r, int x, int y) {
        if(l == x && y == r) return st[rt];
        int mid = (l + r) >> 1;
        push_down(rt);
        if(y <= mid) return query(lc, l, mid, x, y);
        else if(x > mid) return query(rc, mid + 1, r, x, y);
        else return min(query(lc, l, mid, x, mid), query(rc, mid + 1, r, mid + 1, y));
    }
public:
    lazy_min_segtree(int n) :n(n) {
        st.resize((n << 2) + 5, inf);
        lazy.resize((n << 2) + 5, inf);
    }
    lazy_min_segtree(vector<T>& a) {
        n = a.size();
        st.resize((a.size() << 2) + 5, inf);
        lazy.resize((a.size() << 2) + 5, inf);
        build(1, 1, n, a);
    }
    void upd(int pos, T val) { upd(1, 1, n, pos, pos, val); }
    void upd(int x, int y, T val) { upd(1, 1, n, x, y, val); }
    T query(int x, int y) { return query(1, 1, n, x, y); }
#undef lc
#undef rc
};
