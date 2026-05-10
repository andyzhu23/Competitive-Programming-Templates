#include <vector>
#include <algorithm>
// Tarjan's strongly-connected-components algorithm. 0-indexed: pass adjacency of size n, nodes 0..n-1.
namespace cp {
#ifndef CP_TARJAN
#define CP_TARJAN
class Tarjan {
    void tarjan(int u) {
        dfn[u] = low[u] = ++tot;
        stk.push_back(u);
        vis[u] = 1;
        for(int v : e[u]) {
            if(!dfn[v]) {
                tarjan(v);
                low[u] = std::min(low[u], low[v]);
            } else if(vis[v]) low[u] = std::min(low[u], dfn[v]);
        }
        if(low[u] == dfn[u]) {
            ++comp_count;
            while(true) {
                int x = stk.back(); stk.pop_back();
                vis[x] = 0;
                c[x] = comp_count;
                if(x == u) break;
            }
        }
    }

public:
    Tarjan(const std::vector<std::vector<int>>& adj)
        : c(adj.size()), e(adj), low(adj.size()), dfn(adj.size()), vis(adj.size()) {
        int n = (int)adj.size();
        stk.reserve(n);
        for(int i = 0; i < n; ++i) if(!dfn[i]) tarjan(i);
    }

    // One-shot: build a Tarjan from adj and return the SCC label for each node.
    static std::vector<int> scc(const std::vector<std::vector<int>>& adj) { return Tarjan(adj).c; }

    std::vector<int> c;     // c[u] = SCC id of node u; ids are 1..comp_count
    int comp_count = 0;     // total number of SCCs

private:
    std::vector<std::vector<int>> e;
    std::vector<int> low, dfn, stk;
    std::vector<char> vis;
    int tot = 0;
};

#endif // CP_TARJAN
} // namespace cp
