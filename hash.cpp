#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
namespace cp {
#ifndef CP_HASH
#define CP_HASH
template <typename T> class Hash {
    static constexpr int mod = 998'244'353;
    static int base() {
        static const int b = []() {
            std::mt19937 rng((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());
            return std::uniform_int_distribution<int>(257, 1'000'000)(rng);
        }();
        return b;
    }

public:
    template <typename S> Hash(const S& a) : n((int)a.size()), p(n), h(n) {
        const T B = base();
        p[0] = 1;
        for(int i = 1; i < n; ++i) p[i] = p[i - 1] * B % mod;
        h[0] = a[0] % mod;
        for(int i = 1; i < n; ++i) h[i] = (h[i - 1] * B + a[i]) % mod;
    }
    int size() const { return n; }
    T key() const { return h.back(); }
    T get(int l, int r) const {
        if(l == 0) return h[r];
        return (h[r] - h[l - 1] * p[r - l + 1] % mod + mod) % mod;
    }
    bool contains(const Hash<T>& o) const {
        if(n < o.n) return false;
        for(int i = 0; i <= n - o.n; ++i) {
            if(get(i, i + o.n - 1) == o.key()) return true;
        }
        return false;
    }
    // Longest k s.t. suffix-of-len-k of *this equals prefix-of-len-k of o.
    // Linear scan: a longer match does NOT imply a shorter one (suffixes/prefixes shift), so binary search is invalid here.
    int max_concat(const Hash<T>& o) const {
        for(int k = std::min(n, o.n); k >= 1; --k) {
            if(get(n - k, n - 1) == o.get(0, k - 1)) return k;
        }
        return 0;
    }
    int max_pref(const Hash<T>& o) const {
        int lo = 0, hi = std::min(n, o.n), ans = 0;
        while(lo <= hi) {
            int mid = (lo + hi) >> 1;
            if(mid == 0 || get(0, mid - 1) == o.get(0, mid - 1)) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans;
    }
    int max_suf(const Hash<T>& o) const {
        int lo = 0, hi = std::min(n, o.n), ans = 0;
        while(lo <= hi) {
            int mid = (lo + hi) >> 1;
            if(mid == 0 || get(n - mid, n - 1) == o.get(o.n - mid, o.n - 1)) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans;
    }

private:
    int n;
    std::vector<T> p, h;
};

#endif // CP_HASH
} // namespace cp
