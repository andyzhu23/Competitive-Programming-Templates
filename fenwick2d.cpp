/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T> class fenwick2d {
    int n, m;
    template <typename T2> using vec = vector<T2>;
    template <typename T2> T2 lowbit(T2 i) {return i & (-i);}
    vec<vec<T> > d, di, dj, dij;

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

    T query(int x, int y) {
        if(x * y == 0) return 0;
        T ans = 0;
        for(int i = x;i; i -= lowbit(i)) {
            for(int j = y;j; j -= lowbit(j)) {
                ans += (x + 1) * (y + 1) * d[i][j] - (x + 1) * dj[i][j] - (y + 1) * di[i][j] + dij[i][j];
            }
        }
        return ans;
    }

public:

    fenwick2d(int N, int M) {
        n = N + 1, m = M + 1;
        d.resize(n);
        di.resize(n);
        dj.resize(n);
        dij.resize(n);
        for(int i = 0;i<n;++i) {
            d[i].resize(m);
            di[i].resize(m);
            dj[i].resize(m);
            dij[i].resize(m);
        }
    }

    void update(int x, int y, int x2, int y2, T val) {
        update(x, y, val);
        update(x, y2 + 1, -val);
        update(x2 + 1, y, -val);
        update(x2 + 1, y2 + 1, val);
    }

    T query(int x, int y, int x2, int y2) {
        return query(x2, y2) + query(x - 1, y - 1) - query(x2, y - 1) - query(x - 1, y2);
    }
};
