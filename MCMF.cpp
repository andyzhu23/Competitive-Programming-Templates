#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
// Min-cost max-flow via SPFA + blocking-flow DFS.
namespace cp {
#ifndef CP_MCMF
#define CP_MCMF
class MCMF {
    using ll = long long;
    static constexpr ll inf = std::numeric_limits<ll>::max() / 2;
    struct Edge { int u, v; ll cost, cap; int nxt; };

    bool spfa() {
        std::fill(dist.begin(), dist.end(), inf);
        cur = head;
        std::queue<int> q;
        dist[S] = 0;
        q.push(S);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for(int i = head[u]; i; i = e[i].nxt) {
                if(e[i].cap && dist[e[i].v] > dist[u] + e[i].cost) {
                    dist[e[i].v] = dist[u] + e[i].cost;
                    if(!vis[e[i].v]) { vis[e[i].v] = 1; q.push(e[i].v); }
                }
            }
        }
        return dist[T] != inf;
    }
    ll dfs(int u, ll f) {
        if(u == T) { total_cost += dist[T] * f; return f; }
        vis[u] = 1;
        ll ret = 0;
        for(int& i = cur[u]; i; i = e[i].nxt) {
            if(!vis[e[i].v] && e[i].cap && dist[e[i].v] == dist[u] + e[i].cost) {
                ll tmp = dfs(e[i].v, std::min(f, e[i].cap));
                e[i].cap -= tmp;
                e[i ^ 1].cap += tmp;
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
    // Allocates room for graph nodes 1..n plus S=0 and T=n+1. Edges grow dynamically via add().
    MCMF(int n) : S(0), T(n + 1), e(2), head(n + 3), cur(n + 3), dist(n + 3), vis(n + 3) {}
    void reserve_edges(int m) { e.reserve(2 * m + 2); } // pre-allocate for m user-visible edges (each occupies 2 internal slots)

    int source() const { return S; }
    int sink() const { return T; }
    void set_source(int s) { S = s; }
    void set_sink(int t) { T = t; }

    // Pushes the directed edge (u -> v) and its reverse as a pair so e[i ^ 1] is the reverse of e[i].
    // The 2-element dummy prefix in `e` keeps the first real pair at indices (2, 3), preserving the parity.
    void add(int u, int v, ll cost, ll cap) {
        e.push_back({u, v, cost, cap, head[u]});
        head[u] = (int)e.size() - 1;
        e.push_back({v, u, -cost, 0, head[v]});
        head[v] = (int)e.size() - 1;
    }

    // Computes the max flow from source to sink (with min cost). Use cost() to read the accumulated cost afterward.
    ll max_flow() {
        ll total_flow = 0;
        while(spfa()) total_flow += dfs(S, inf);
        return total_flow;
    }
    ll cost() const { return total_cost; }

private:
    int S, T;
    std::vector<Edge> e;
    std::vector<int> head, cur;
    std::vector<ll> dist;
    std::vector<char> vis;
    ll total_cost = 0;
};

#endif // CP_MCMF
} // namespace cp
