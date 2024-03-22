#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> f, sz;
    int n;
public: 
    DSU(int n) :n(n) {
        f.resize(n + 1);
        sz.resize(n + 1);
        iota(f.begin(), f.end(), 0);
    }
    int Find(int x) { return f[x] == x ? x : f[x] = Find(f[x]); }
    bool merge(int u, int v) {
        int fu = Find(u);
        int fv = Find(v);
        if(fu == fv) return 0;
        f[fv] = fu;
        sz[fu] += fv;
        return 1;
    }
    bool same(int u, int v) {
        int fu = Find(u);
        int fv = Find(v);
        return fu == fv;
    }
};
