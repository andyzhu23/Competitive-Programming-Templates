/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;

const int N = ;
vector<int> e[N];
int n;
template <typename T> class lazy_sum_segtree {
    vector<T> st, lazy;
    int n;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    void push_up(int rt) {
        st[rt] = st[lc] + st[rc];
    }
    void push_down(int rt, int l, int r, int mid) {
        st[lc] += (mid - l + 1) * lazy[rt];
        st[rc] += (r - mid) * lazy[rt];
        lazy[lc] += lazy[rt];
        lazy[rc] += lazy[rt];
        lazy[rt] = 0;
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
            st[rt] += (r - l + 1) * val;
            lazy[rt] += val;
            return;
        }
        int mid = (l + r) >> 1;
        push_down(rt, l, r, mid);
        if(y <= mid) upd(lc, l, mid, x, y, val);
        else if(x > mid) upd(rc, mid + 1, r, x, y, val);
        else upd(lc, l, mid, x, mid, val), upd(rc, mid + 1, r, mid + 1, y, val);
        push_up(rt);
    }
    T query(int rt, int l, int r, int x, int y) {
        if(l == x && y == r) return st[rt];
        int mid = (l + r) >> 1;
        push_down(rt, l, r, mid);
        if(y <= mid) return query(lc, l, mid, x, y);
        else if(x > mid) return query(rc, mid + 1, r, x, y);
        else return query(lc, l, mid, x, mid) + query(rc, mid + 1, r, mid + 1, y);
    }
public:
    lazy_sum_segtree(int n) :n(n) {
        st.resize((n << 2) + 5);
        lazy.resize((n << 2) + 5);
    }
    lazy_sum_segtree(vector<T>& a) {
        n = a.size();
        st.resize((a.size() << 2) + 5);
        lazy.resize((a.size() << 2) + 5);
        build(1, 1, n, a);
    }
    void upd(int pos, T val) { upd(1, 1, n, pos, pos, val); }
    void upd(int x, int y, T val) { upd(1, 1, n, x, y, val); }
    T query(int x, int y) { return query(1, 1, n, x, y); }
#undef lc
#undef rc
};
lazy_sum_segtree<long long> st(N);
struct HLD {
    using ll = long long;
    int top[N], siz[N], dfn[N], rnk[N], hson[N], dep[N], w[N], f[N];
    int tot;
    void dfs1(int u = 1, int fa = 0) {
        f[u] = fa;
        dep[u] = dep[fa] + 1;
        siz[u] = 1;
        for(int v : e[u]) {
            if(v == fa) continue;
            dfs1(v, u);
            siz[u] += siz[v];
            if(siz[hson[u]] <= siz[v]) hson[u] = v;
        }
    }
    void dfs2(int u = 1, int fa = 0, int tp = 1) {
        dfn[u] = ++tot;
        rnk[tot] = u;
        st.upd(tot, w[u]);
        top[u] = tp;
        if(hson[u] == 0) return;
        dfs2(hson[u], u, tp);
        for(int v : e[u]) {
            if(v == fa || v == hson[u]) continue;
            dfs2(v, u, v);
        }
    }
    void update(int pos, int val) {
        w[pos] = val;
        pos = dfn[pos];
        st.upd(pos, val);
    }
    void update(int u, int v, int val) {
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            st.upd(dfn[top[u]], dfn[u], val);
            u = f[top[u]];
        }
        st.upd(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), val);
    }
    ll query(int u, int v) {
        ll ans = 0;
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            ans += st.query(dfn[top[u]], dfn[u]);
            u = f[top[u]];
        }
        return ans + st.query(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]));
    }
};
