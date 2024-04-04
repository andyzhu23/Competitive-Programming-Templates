/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;

// using mt = mint<>;
namespace combinatorics {
    vector<mt> _fac, _ifac;
    int _size = -1;

    void _resize(int x) {
        if(_size <= 0) _size = 1;
        while(_size <= x) {
            _size <<= 1;
        }
        _fac.resize(_size + 1);
        _ifac.resize(_size + 1);
        _fac[0] = 1;
        for(int i = 1;i<=_size;++i) _fac[i] = _fac[i - 1] * i;
        _ifac[_size] = 1 / _fac[_size];
        for(int i = _size - 1;~i;--i) _ifac[i] = _ifac[i + 1] * (i + 1);
    }

    mt fac(int x) {
        assert(x >= 0);
        if(x > _size) _resize(x);
        return _fac[x];
    }
    mt ifac(int x) {
        assert(x >= 0);
        if(x > _size) _resize(x);
        return _ifac[x];
    }
    mt nCr(int a, int b) {
        if(a < b || a < 0 || b < 0) return 0;
        return fac(a) * ifac(b) * ifac(a - b);
    }
    mt nPr(int a, int b) {
        if(a < b || a < 0 || b < 0) return 0;
        return fac(a) * ifac(b);
    }
}
using namespace combinatorics;
