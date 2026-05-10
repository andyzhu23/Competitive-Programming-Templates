#include <vector>
#include <algorithm>
#include <bit>
// 0-indexed sparse table for idempotent associative ops (min/max/gcd). Edit op() to change the combine.
namespace cp {
#ifndef CP_SPARSE_TABLE
#define CP_SPARSE_TABLE
template <typename T> class sparse_table {
    static T op(T a, T b) { return std::min(a, b); }

public:
    sparse_table() = default;
    sparse_table(const std::vector<T>& v) : n((int)v.size()), st(std::bit_width((unsigned)n), std::vector<T>(n)) {
        st[0] = v;
        for(int i = 1; i < (int)st.size(); ++i) {
            for(int j = 0; j + (1 << i) <= n; ++j)
                st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
    // Inclusive range [l, r].
    T query(int l, int r) const {
        int sz = (int)std::bit_width((unsigned)(r - l + 1)) - 1;
        return op(st[sz][l], st[sz][r - (1 << sz) + 1]);
    }

private:
    int n = 0;
    std::vector<std::vector<T>> st;
};

#endif // CP_SPARSE_TABLE
} // namespace cp
