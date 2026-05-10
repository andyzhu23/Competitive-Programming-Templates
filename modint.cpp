#include <iostream>
namespace cp {
#ifndef CP_MODINT
#define CP_MODINT
template <int mod = 998'244'353> class modint {
    static void exgcd(int a, int b, int& x, int& y) noexcept {
        if((long long)a * b == 0) { x = 1; y = 0; return; }
        exgcd(b, a % b, x, y);
        int tmp = y; y = x - a / b * y; x = tmp;
    }

public:
    modint() noexcept : v(0) {}
    template <typename T> modint(T _v) noexcept : v((int)(_v % mod)) { v = (v + mod) % mod; }
    explicit operator int() const noexcept { return v; }
    int val() const noexcept { return v; }

    modint operator-() const noexcept { return modint((-v + mod) % mod); }
    modint inv() const noexcept { int x, y; exgcd(v, mod, x, y); return modint((x % mod + mod) % mod); }

    modint& operator+=(modint o) noexcept { v = (v + o.v) % mod; return *this; }
    modint& operator-=(modint o) noexcept { v = (v - o.v + mod) % mod; return *this; }
    modint& operator*=(modint o) noexcept { v = (int)((long long)v * o.v % mod); return *this; }
    modint& operator/=(modint o) noexcept { return *this *= o.inv(); }

    friend modint operator+(modint a, modint b) noexcept { return a += b; }
    friend modint operator-(modint a, modint b) noexcept { return a -= b; }
    friend modint operator*(modint a, modint b) noexcept { return a *= b; }
    friend modint operator/(modint a, modint b) noexcept { return a /= b; }

    modint& operator++() noexcept { return *this += 1; }
    modint& operator--() noexcept { return *this -= 1; }
    modint operator++(int) noexcept { modint old = *this; ++*this; return old; }
    modint operator--(int) noexcept { modint old = *this; --*this; return old; }

    friend bool operator==(modint a, modint b) noexcept { return a.v == b.v; }
    friend bool operator!=(modint a, modint b) noexcept { return a.v != b.v; }

    friend std::ostream& operator<<(std::ostream& os, modint a) { return os << a.v; }
    friend std::istream& operator>>(std::istream& is, modint& a) { long long x; is >> x; a = modint(x); return is; }

private:
    int v;
};

#endif // CP_MODINT
} // namespace cp
