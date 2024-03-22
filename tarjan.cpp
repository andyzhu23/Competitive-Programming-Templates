/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;

const int N = ;
vector<int> e[N];
vector<int> stk;
int tot, color;
int low[N], dfn[N], c[N];
bitset<N> vis;

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    stk.push_back(u);
    vis[u] = 1;
    for (int v : e[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]) {
        ++color;
        while(stk.back() != u) {
            c[stk.back()] = color;
            vis[stk.back()] = 0;
            stk.pop_back();
        }
        vis[stk.back()] = 0;
        stk.pop_back();
    }
}
