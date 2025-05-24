/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;

class Dinic {
    using ll = long long;
    const ll inf = 0x3f3f3f3f3f3f3f3f;
    int n, m, tot = 1;
    vector<ll> a, dist;
    ll ans;
    struct edge {
        int u, v;
        ll w, f;
        int nxt;
    };
    vector<edge> e;
    vector<int> head, cur;
    vector<bool> vis;

public:
    int S, T;
    Dinic(int n, int m) :n(n + 1), m(m + 1), S(0), T(n + 1), tot(1), ans(0), a(n + 3), dist(n + 3), e(m + 2), head(n + 3), vis(n + 3) {}

    void add(int u, int v, ll w, ll f) {
        e[++tot] = {u, v, w, f, head[u]};
        head[u] = tot;
        e[++tot] = {v, u, -w, 0, head[v]};
        head[v] = tot;
    }


    bool spfa() {
        queue<int> q;
        q.push(S);
        for(auto& x : dist) x = inf;
        cur = head;
        dist[S] = 0;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for(int i = head[u];i;i=e[i].nxt) {
                if(e[i].f && dist[e[i].v] > dist[u] + e[i].w) {
                    dist[e[i].v] = dist[u] + e[i].w;
                    if(!vis[e[i].v]) {
                        vis[e[i].v] = 1;
                        q.push(e[i].v);
                    }
                }
            }
        }
        return dist[T] != inf;
    }

private:
    ll dfs(int u, ll f) {
        if(u == T) {
            ans += dist[T] * f;
            return f;
        }
        vis[u] = 1;
        ll ret = 0;
        for(int& i = cur[u];i;i=e[i].nxt) {
            if(!vis[e[i].v] && e[i].f && dist[e[i].v] == dist[u] + e[i].w) {
                ll tmp = dfs(e[i].v, min(f, e[i].f));
                e[i].f -= tmp;
                e[i ^ 1].f += tmp;
                f -= tmp;
                ret += tmp;
                if(f == 0) break;
            }
        }
        vis[u] = 0;
        if(ret == 0) dist[u] = 0;
        return ret;
    }

public:
    ll dfs() { return dfs(S, inf); }

    ll dinic() {
        ll ans = 0;
        while(spfa()) ans += dfs();
        return ans;
    }

    ll cost() { return ans; }
};
