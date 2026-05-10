#include <vector>
#include <numeric>
namespace cp {
#ifndef CP_DSU
#define CP_DSU
class DSU {
public:
    DSU(int n) : f(n + 1), sz(n + 1, 1) {
        std::iota(f.begin(), f.end(), 0);
    }
    int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
    bool merge(int u, int v) {
        int fu = find(u);
        int fv = find(v);
        if(fu == fv) return false;
        f[fv] = fu;
        sz[fu] += sz[fv];
        return true;
    }
    bool same(int u, int v) { return find(u) == find(v); }
    int size(int x) { return sz[find(x)]; }

private:
    std::vector<int> f, sz;
};
#endif // CP_DSU
} // namespace cp
