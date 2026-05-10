#include <vector>
// 2D Fenwick tree with range-update and range-query, using four 2D BITs.
namespace cp {
#ifndef CP_FENWICK2D
#define CP_FENWICK2D
template <typename T> class fenwick2d {
    static int lowbit(int i) { return i & -i; }

    void update(int x, int y, T val) {
        for(int i = x; i < n; i += lowbit(i)) {
            for(int j = y; j < m; j += lowbit(j)) {
                d[i][j] += val;
                di[i][j] += val * x;
                dj[i][j] += val * y;
                dij[i][j] += val * x * y;
            }
        }
    }
    T query(int x, int y) const {
        if(x * y == 0) return 0;
        T ans = 0;
        for(int i = x; i; i -= lowbit(i)) {
            for(int j = y; j; j -= lowbit(j)) {
                ans += (x + 1) * (y + 1) * d[i][j] - (x + 1) * dj[i][j] - (y + 1) * di[i][j] + dij[i][j];
            }
        }
        return ans;
    }

public:
    fenwick2d(int n, int m)
        : n(n + 1), m(m + 1),
          d(n + 1, std::vector<T>(m + 1)), di(n + 1, std::vector<T>(m + 1)),
          dj(n + 1, std::vector<T>(m + 1)), dij(n + 1, std::vector<T>(m + 1)) {}

    void update(int x, int y, int x2, int y2, T val) {
        update(x, y, val);
        update(x, y2 + 1, -val);
        update(x2 + 1, y, -val);
        update(x2 + 1, y2 + 1, val);
    }
    T query(int x, int y, int x2, int y2) const {
        return query(x2, y2) + query(x - 1, y - 1) - query(x2, y - 1) - query(x - 1, y2);
    }

private:
    int n, m;
    std::vector<std::vector<T>> d, di, dj, dij;
};

#endif // CP_FENWICK2D
} // namespace cp
