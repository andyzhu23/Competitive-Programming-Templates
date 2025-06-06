/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> f, sz;
    int n;
public: 
    DSU(int n) :n(n), f(n + 1), sz(n + 1, 1) {
        iota(f.begin(), f.end(), 0);
    }
    int Find(int x) { return f[x] == x ? x : f[x] = Find(f[x]); }
    bool merge(int u, int v) {
        int fu = Find(u);
        int fv = Find(v);
        if(fu == fv) return 0;
        f[fv] = fu;
        sz[fu] += sz[fv];
        return 1;
    }
    bool same(int u, int v) {
        int fu = Find(u);
        int fv = Find(v);
        return fu == fv;
    }
    int size(int x) { return sz[Find(x)]; }
};
