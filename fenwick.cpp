#include <bits/stdc++.h>
using namespace std;

template <typename T> class fenwick {
    int n;
    vector<T> d, muld;
    void update(int x, T val){
        assert(x > 0);
        for(int i = x;i<=n;i+=i&(-i)) {
            d[i] += val;
            muld[i] += (x - 1) * val;
        }
    }

public:
    fenwick(int n) :n(n) {
        d.resize(n + 1);
        muld.resize(n + 1);
    }
    int size() { return n; }
    void upd(int a, int b, T val) {
        update(a, val);
        update(b + 1, val * (-1));
    }
    void upd(int a, T val) { upd(a, a, val); }
    T query(int x){
        T ans = 0;
        for(int i = x;i;i-=i&(-i)) {
            ans += x * d[i] - muld[i];
        }
        return ans;
    }
    T query(int a, int b) {
        return query(b) - query(a - 1);
    }
};
