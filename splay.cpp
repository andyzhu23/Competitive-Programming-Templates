/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T> class splay_tree {
    vector<int> size, fa, lc, rc, cnt;
    vector<T> val;
    int root, tot, n;
#define chk(rt) (rc[fa[rt]] != rt)


    void update(int rt) {
        size[rt] = size[lc[rt]] + size[rc[rt]] + cnt[rt];
        fa[lc[rt]] = fa[rc[rt]] = rt;
    }
    void turn(int x) {
        int y = fa[x];
        int z = fa[y];
        int tmp;
        if(chk(x)) {
            // right turn
            tmp = rc[x];
            rc[x] = y;
            lc[y] = tmp;
        } else {
            // left turn
            tmp = lc[x];
            lc[x] = y;
            rc[y] = tmp;
        }
        fa[tmp] = y;
        fa[y] = x;
        fa[x] = z;
        lc[z] == y ? lc[z] = x : rc[z] = x;
        update(y);
        update(x);
    }

    void splay(int rt) {
        while(fa[rt]) {
            if(fa[fa[rt]]) {
                if(chk(fa[rt]) == chk(rt)) turn(fa[rt]);
                else turn(rt);
            }
            turn(rt);
        }
        root = rt;
    }

    void insert(int& rt, T x) {
        if(rt == 0) {
            rt = ++tot;
            size[rt] = 1;
            cnt[rt] = 1;
            val[rt] = x;
            return;
        } else if(val[rt] == x) cnt[rt]++;
        else if(val[rt] > x) insert(lc[rt], x);
        else insert(rc[rt], x);
        update(rt);
    }

    int Find(int& rt, T x) {
        if(rt == 0) return -1;
        if(val[rt] == x) {
            splay(rt);
            return root;
        }
        else if(val[rt] > x) return Find(lc[rt], x);
        else return Find(rc[rt], x);
    }

    int preans;
    void pre(int& rt, T x) {
        if(rt == 0) return;
        if(val[rt] < x) {
            preans = rt;
            pre(rc[rt], x);
        } else pre(lc[rt], x);
    }

    int succans;
    void succ(int& rt, T x) {
        if(rt == 0) return;
        if(val[rt] > x) {
            succans = rt;
            succ(lc[rt], x);
        } else succ(rc[rt], x);
    }

    int rnk(int& rt, T x) {
        if(rt == 0) return 0;
        if(val[rt] == x) return size[lc[rt]] + 1;
        else if(val[rt] > x) return rnk(lc[rt], x);
        else return rnk(rc[rt], x) + size[lc[rt]] + cnt[rt];
    }

    T id(int& rt, int x) {
        if(rt == 0) return 0;
        if(size[lc[rt]] >= x) return id(lc[rt], x);
        else if(size[lc[rt]] + cnt[rt] >= x) return val[rt];
        else return id(rc[rt], x - size[lc[rt]] - cnt[rt]);
    }

    int Max(int& rt) {
        if(rc[rt]) return Max(rc[rt]);
        else return rt;
    }

    int join(int& x, int& y) {
        if(x * y == 0) return x + y;
        int rt = Max(x);
        splay(rt);
        root = rt;
        rc[rt] = y;
        fa[y] = rt;
        update(root);
        return rt;
    }

#undef chk(rt)

public:

    splay_tree(int n) :n(n) {
        size.resize(n);
        fa.resize(n);
        lc.resize(n);
        rc.resize(n);
        cnt.resize(n);
        val.resize(n);
        tot = 0;
    }

    void erase(T x) {
        int rt = Find(root, x);
        if(rt == -1 || !rt) return;
        if(--cnt[rt] > 0) {
            update(rt);
            return;
        }
        root = join(lc[rt], rc[rt]);
        fa[root] = 0;
    }


    void insert(T x) { insert(root, x); splay(Find(root, x)); }

    int Find(T x) { return Find(root, x); }

    int pre(T x) {
        pre(root, x);
        return preans;
    }

    int succ(T x) {
        succ(root, x);
        return succans;
    }

    int rnk(T x) { return rnk(root, x); }

    T id(int x) { return id(root, x); }

    int max() { return Max(root); }
    
    void print(int rt){
        if(rt == 0) return;
        printf("rt: %d, lc:%d, rc:%d, sz:%d, cnt:%d, father:%d\n", rt, lc[rt], rc[rt], size[rt], cnt[rt], fa[rt]);
        print(lc[rt]);
        print(rc[rt]);
    }

};
