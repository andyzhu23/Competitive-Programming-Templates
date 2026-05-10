#include <vector>
#include <unordered_map>
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

#ifndef CP_VIRTUAL_TREE
#define CP_VIRTUAL_TREE
class virtual_tree {
public:
    virtual_tree(const std::vector<std::vector<int>>& adj, int root = 1) : lca(adj, root) {}

    // Build a virtual tree over `nodes` (the key vertices).
    // Returns {root, e} where e[u] -> children of u in the compressed tree, and root is the topmost node by depth.
    // Use structured binding: auto [root, e] = vt.build_virtual({...});
    // Pass `nodes` by value: the algorithm mutates it (sorts and augments with LCAs), so the caller's vector is left alone.
    std::pair<int, std::unordered_map<int, std::vector<int>>> build_virtual(std::vector<int> nodes) const {
        std::unordered_map<int, std::vector<int>> e;
        if(nodes.empty()) return {0, e};
        auto by_entry = [&](int a, int b) { return lca.entry_time(a) < lca.entry_time(b); };
        std::sort(nodes.begin(), nodes.end(), by_entry);
        int n = (int)nodes.size();
        for(int i = 1; i < n; ++i) nodes.push_back(lca.lca(nodes[i], nodes[i - 1]));
        std::sort(nodes.begin(), nodes.end(), by_entry);
        nodes.erase(std::unique(nodes.begin(), nodes.end()), nodes.end());
        int root = nodes[0];
        for(int i = 1; i < (int)nodes.size(); ++i) {
            if(lca.depth(nodes[i]) < lca.depth(root)) root = nodes[i];
            int p = lca.lca(nodes[i], nodes[i - 1]);
            if(nodes[i] != p) e[p].push_back(nodes[i]);
        }
        return {root, e};
    }

private:
    LCA lca;
};
#endif // CP_VIRTUAL_TREE
} // namespace cp
