#include <vector>
#include <algorithm>
#include <bit>
namespace cp {
#ifndef CP_LCA
#define CP_LCA
class LCA {
    void dfs(int u, int p, const std::vector<std::vector<int>>& adj) {
        tin[u] = ++tot;
        dep[u] = (u == p) ? 0 : dep[p] + 1;
        up[u][0] = p;
        for(int i = 1; i < LOG; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
        for(int v : adj[u]) if(v != p) dfs(v, u, adj);
    }

public:
    LCA(const std::vector<std::vector<int>>& adj, int root)
        : n((int)adj.size()), LOG(std::max(1, (int)std::bit_width((unsigned)n))),
          dep(n), tin(n), up(n, std::vector<int>(LOG, root)) {
        dfs(root, root, adj);
    }
    int lca(int u, int v) const {
        if(dep[u] < dep[v]) std::swap(u, v);
        for(int i = LOG - 1; i >= 0; --i)
            if(dep[up[u][i]] >= dep[v]) u = up[u][i];
        if(u == v) return u;
        for(int i = LOG - 1; i >= 0; --i)
            if(up[u][i] != up[v][i]) { u = up[u][i]; v = up[v][i]; }
        return up[u][0];
    }
    int depth(int u) const { return dep[u]; }
    int entry_time(int u) const { return tin[u]; }

private:
    int n;
    int LOG;
    std::vector<int> dep, tin;
    std::vector<std::vector<int>> up;
    int tot = 0;
};
#endif // CP_LCA
} // namespace cp
