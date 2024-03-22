/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T> class segtree {
    vector<T> st;
    int n;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    void push_up(int rt) {
        st[rt] = st[lc] + st[rc];
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
    void upd(int rt, int l, int r, int pos, T val) {
        if(l == r) {
            st[rt] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) upd(lc, l, mid, pos, val);
        else upd(rc, mid + 1, r, pos, val);
        push_up(rt);
    }
    T query(int rt, int l, int r, int x, int y) {
        if(l == x && y == r) return st[rt];
        int mid = (l + r) >> 1;
        if(y <= mid) return query(lc, l, mid, x, y);
        else if(x > mid) return query(rc, mid + 1, r, x, y);
        else return query(lc, l, mid, x, mid) + query(rc, mid + 1, r, mid + 1, y);
    }
public:
    segtree(int n) :n(n) {
        st.resize((n << 2) + 5);
    }
    segtree(vector<T>& a) {
        n = a.size();
        st.resize((a.size() << 2) + 5);
        build(1, 1, n, a);
    }
    void upd(int pos, T val) { upd(1, 1, n, pos, val); }
    T query(int x, int y) { return query(1, 1, n, x, y); }
#undef lc
#undef rc
};
