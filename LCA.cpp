#include <bits/stdc++.h>
using namespace std;

const int N = ;
vector<int> e[N];
int f[N][22], dep[N];
int dfn[N], tot;
void dfs(int u = 1, int fa = 0) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    dfn[u] = ++tot;
    for(int i = 1;i<22;++i) f[u][i] = f[f[u][i - 1]][i - 1];
    for(int v : e[u]) if(v != fa) {
        dfs(v, u);
    }
}
int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 21;~i;--i) {
        if(dep[f[u][i]] >= dep[v]) u = f[u][i];
        if(u == v) return u;
    }
    for(int i = 21;~i;--i) {
        if(f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}
