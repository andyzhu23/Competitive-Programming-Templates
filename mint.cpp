/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

template <int mod = 998'244'353> class mint {
    // obtaining inverse
    void exgcd(int a, int b, int& x, int& y) {
        if(1ll * a * b == 0) { x = 1, y = 0; return; }
        exgcd(b, a % b, x, y); int tmp = y; y = x - a / b * y; x = tmp; 
    }
public:
    int v;
    explicit operator int() const { return v; }

    // constructors
    mint():v(0) {}
    template <typename T> mint(T _v) :v((int)(_v % mod)) { v = (v + mod) % mod; }

    template <typename T> mint& operator=(T a) { v = (a + mod) % mod; return *this; }
    mint operator-() { return mint((-v + mod) % mod); } 
    mint& operator+=(mint o) { v = (v + o.v) % mod; return *this; }
    mint& operator-=(mint o) { v = (v - o.v + mod) % mod; return *this; }
    mint inv() { int x, y; exgcd(v, mod, x, y); return mint((x + mod) % mod); }
    mint& operator*=(mint o) { v = (long long)v * o.v % mod; return *this; }
    mint& operator/=(mint o) { v = (long long)v * o.inv().v % mod; return *this; }

    mint operator+(mint o) { return mint((v + o.v) % mod); } 
    mint operator-(mint o) { return mint((v - o.v + mod) % mod); } 
    mint operator*(mint o) { return mint((long long)v * o.v % mod); } 
    mint operator/(mint o) { return mint((long long)v * o.inv().v % mod); }

    template <typename T> mint& operator+=(T o) { v = (v + o) % mod; return *this; }
    template <typename T> mint& operator-=(T o) { v = (v - o + mod) % mod; return *this; }
    template <typename T> mint& operator*=(T o) { v = (long long)v * o % mod; return *this; }
    template <typename T> mint& operator/=(T o) { v = (long long)v * mint(o).inv().v % mod; return *this; }

    template <typename T> mint operator+(T o) { return mint((v + o) % mod); } 
    template <typename T> mint operator-(T o) { return mint((v - o + mod) % mod); } 
    template <typename T> mint operator*(T o) { return mint((long long)v * o % mod); } 
    template <typename T> mint operator/(T o) { return mint((long long)v * mint(o).inv().v % mod); }

    mint& operator++() { v = (v + 1) % mod; return *this; }
    mint& operator--() { v = (v - 1 + mod) % mod; return *this; }

    mint operator++(int) { mint old = *this; operator++(); return old; }
    mint operator--(int) { mint old = *this; operator--(); return old; }

    bool operator==(mint o) { return v == o.v; }
    bool operator!=(mint o) { return v != o.v; }

    template <typename T> bool operator==(T o) { return v == o; }
    template <typename T> bool operator!=(T o) { return v != o; }
    
    template <typename T> friend mint operator+(T o, mint x) { return x + o; }
    template <typename T> friend mint operator-(T o, mint x) { return x * (-1) + o; }
    template <typename T> friend mint operator*(T o, mint x) { return x * o; }
    template <typename T> friend mint operator/(T o, mint x) { return x.inv() * o; }

    template <typename T> mint& operator%=(T o) { v %= o; return *this; }
    template <typename T> friend T operator%(T o, mint x) { return o % x.v; }
    template <typename T> friend mint operator%(mint x, T o) { return mint(x.v % o); }
    
    friend std::ostream& operator<<(std::ostream& os, mint const& a) { return os << a.v; }
    friend istream& operator>>(istream& is, mint& a) { long long x; is >> x; a = mint(x); return is; }
};

