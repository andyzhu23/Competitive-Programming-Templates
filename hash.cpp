/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define random(a, b) rng() % (b - a + 1) + a

int MOD = 998244853;
int BASE = random(120, 10000);
template <typename T> class Hash {
    int n;
    vector<T> p;
    const int mod = MOD;
    const int base = BASE;
    vector<T> h;
public:
    template <typename S> Hash(S a) : n(a.size()), h(n), p(n) {
        p[0] = 1;
         for(int i = 1;i<n;++i) p[i] = p[i - 1] * base % mod;
        h[0] = a[0] % mod;
        for(int i = 1;i<h.size();++i) h[i] = (h[i - 1] * base + a[i]) % mod;
    }
    int size() { return h.size(); }
    T key() { return h.back(); }
    T get(int l, int r) {
         if (l == 0) return h[r];
        return (h[r] - h[l - 1] * p[r - l + 1] % mod + mod) % mod;
    }
    bool contains(Hash<T>& o) {
     if(h.size() < o.size()) return 0;
        for(int i = 0;i<=h.size() - o.size();++i) {
            if(get(i, i + o.size() - 1) == o.key()) {
                return 1;
            }
        }
        return 0;
    }
    int max_concat(Hash<T>& o) {
        for(int k = min(size(), o.size());k>=1;--k) {
            if(get(size() - k, size() - 1) == o.get(0, k - 1)) {
                return k;
            }
        }
        return 0;
    }
    int max_pref(Hash<T>& o) {
        int lo = 0, hi = min(size(), o.size());
        int ans = 0;
        while(lo <= hi) {
            int mid = (lo + hi) >> 1;
            if(get(0, mid - 1) == o.get(0, mid - 1)) {
                ans = mid;
                lo = mid + 1;
            } else hi = mid - 1;
        }
        return ans;
    }
    int max_suf(Hash<T>& o) {
        int lo = 0, hi = min(size(), o.size());
        int ans = 0;
        while(lo <= hi) {
            int mid = (lo + hi) >> 1;
            if(get(size() - mid, size() - 1) == o.get(o.size() - mid, o.size() - 1)) {
                ans = mid;
                lo = mid + 1;
            } else hi = mid - 1;
        }
        return ans;
    }
};