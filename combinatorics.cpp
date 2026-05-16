#include <vector>
// Requires a modular-int type with arithmetic and 1/x; instantiate as e.g. Combinatorics<modint<>>.
namespace cp {
#ifndef CP_COMBINATORICS
#define CP_COMBINATORICS
template <typename mt> class Combinatorics {
    void resize(int x) {
        if(cap <= 0) cap = 1;
        while(cap <= x) cap <<= 1;
        _fac.resize(cap + 1);
        _ifac.resize(cap + 1);
        _fac[0] = 1;
        for(int i = 1; i <= cap; ++i) _fac[i] = _fac[i - 1] * i;
        _ifac[cap] = mt(1) / _fac[cap];
        for(int i = cap - 1; i >= 0; --i) _ifac[i] = _ifac[i + 1] * (i + 1);
    }

public:
    Combinatorics(int n) { resize(n); }
    Combinatorics() : Combinatorics(1) {}

    mt fac(int x) { if(x > cap) resize(x); return _fac[x]; }
    mt ifac(int x) { if(x > cap) resize(x); return _ifac[x]; }
    mt nCr(int a, int b) {
        if(a < b || a < 0 || b < 0) return 0;
        return fac(a) * ifac(b) * ifac(a - b);
    }
    mt nPr(int a, int b) {
        if(a < b || a < 0 || b < 0) return 0;
        return fac(a) * ifac(a - b);
    }

private:
    std::vector<mt> _fac, _ifac;
    int cap = 0;
};

#endif // CP_COMBINATORICS
} // namespace cp
