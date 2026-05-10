#include <vector>
#include <cassert>
// Range-add, range-sum-query Fenwick tree using two BITs (Mishra's trick).
// Two BITs (d, muld) store deltas so that prefix_sum(x) = x * sum_of_d - sum_of_muld.
namespace cp {
#ifndef CP_FENWICK
#define CP_FENWICK
template <typename T> class fenwick {
    void update(int x, T val) {
        assert(x > 0);
        for(int i = x; i <= n; i += i & -i) {
            d[i] += val;
            muld[i] += (x - 1) * val;
        }
    }

public:
    fenwick() = default;
    fenwick(int n) : n(n), d(n + 1), muld(n + 1) {}
    void resize(int N) { n = N; d.resize(n + 1); muld.resize(n + 1); }

    int size() const { return n; }
    void upd(int a, int b, T val) {
        update(a, val);
        update(b + 1, -val);
    }
    void upd(int a, T val) { upd(a, a, val); }
    T query(int x) const {
        T ans = 0;
        for(int i = x; i; i -= i & -i) ans += x * d[i] - muld[i];
        return ans;
    }
    T query(int a, int b) const { return query(b) - query(a - 1); }

private:
    int n = 0;
    std::vector<T> d, muld;
};

#endif // CP_FENWICK
} // namespace cp
