#include <vector>
#include <algorithm>
namespace cp {
#ifndef CP_LAZY_SUM_SEGTREE
#define CP_LAZY_SUM_SEGTREE
template <typename T> class lazy_sum_segtree {
    static constexpr int lc(int rt) { return rt << 1; }
    static constexpr int rc(int rt) { return rt << 1 | 1; }

    void push_up(int rt) { st[rt] = st[lc(rt)] + st[rc(rt)]; }
    void push_down(int rt, int l, int r, int mid) {
        st[lc(rt)] += (mid - l + 1) * lazy[rt];
        st[rc(rt)] += (r - mid) * lazy[rt];
        lazy[lc(rt)] += lazy[rt];
        lazy[rc(rt)] += lazy[rt];
        lazy[rt] = 0;
    }
    void upd(int rt, int l, int r, int x, int y, T val) {
        if(l == x && y == r) {
            st[rt] += (r - l + 1) * val;
            lazy[rt] += val;
            return;
        }
        int mid = (l + r) >> 1;
        push_down(rt, l, r, mid);
        if(y <= mid) upd(lc(rt), l, mid, x, y, val);
        else if(x > mid) upd(rc(rt), mid + 1, r, x, y, val);
        else upd(lc(rt), l, mid, x, mid, val), upd(rc(rt), mid + 1, r, mid + 1, y, val);
        push_up(rt);
    }
    T query(int rt, int l, int r, int x, int y) {
        if(l == x && y == r) return st[rt];
        int mid = (l + r) >> 1;
        push_down(rt, l, r, mid);
        if(y <= mid) return query(lc(rt), l, mid, x, y);
        else if(x > mid) return query(rc(rt), mid + 1, r, x, y);
        else return query(lc(rt), l, mid, x, mid) + query(rc(rt), mid + 1, r, mid + 1, y);
    }

public:
    lazy_sum_segtree(int n) : n(n), st((n << 2) + 5), lazy((n << 2) + 5) {}
    void upd(int pos, T val) { upd(1, 1, n, pos, pos, val); }
    void upd(int x, int y, T val) { upd(1, 1, n, x, y, val); }
    T query(int x, int y) { return query(1, 1, n, x, y); }

private:
    int n;
    std::vector<T> st, lazy;
};
#endif // CP_LAZY_SUM_SEGTREE

#ifndef CP_HLD
#define CP_HLD
class HLD {
    using ll = long long;

    void dfs1(int u, int fa) {
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
    void dfs2(int u, int fa, int tp) {
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

public:
    // adj and weights are 1-indexed: adj[0] / weights[0] unused; n = adj.size() - 1.
    HLD(const std::vector<std::vector<int>>& adj, const std::vector<ll>& weights, int root = 1)
        : n((int)adj.size() - 1), e(adj),
          top(n + 1), siz(n + 1), dfn(n + 1), rnk(n + 1), hson(n + 1), dep(n + 1), f(n + 1),
          w(weights), st(n) {
        dfs1(root, 0);
        dfs2(root, 0, root);
    }
    void update(int pos, ll val) {
        st.upd(dfn[pos], val - w[pos]);
        w[pos] = val;
    }
    void update(int u, int v, ll val) {
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) std::swap(u, v);
            st.upd(dfn[top[u]], dfn[u], val);
            u = f[top[u]];
        }
        st.upd(std::min(dfn[u], dfn[v]), std::max(dfn[u], dfn[v]), val);
    }
    ll query(int u, int v) {
        ll ans = 0;
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) std::swap(u, v);
            ans += st.query(dfn[top[u]], dfn[u]);
            u = f[top[u]];
        }
        return ans + st.query(std::min(dfn[u], dfn[v]), std::max(dfn[u], dfn[v]));
    }

private:
    int n;
    std::vector<std::vector<int>> e;
    std::vector<int> top, siz, dfn, rnk, hson, dep, f;
    std::vector<ll> w;
    lazy_sum_segtree<ll> st;
    int tot = 0;
};

#endif // CP_HLD
} // namespace cp
