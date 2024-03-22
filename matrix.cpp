/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T, int N> class matrix {
    array<array<T, N>, N> a;
public:
    matrix() {
        for(auto& x : a) {
            for(auto& y : x) y = 0;
        }
    }
    matrix(array<array<T, N>, N>& tmp) {
        for(int i = 0;i<N;++i) {
            for(int j = 0;j<N;++j) {
                a[i][j] = tmp[i][j];
            }
        }
    }
    matrix operator=(matrix tmp) {
        for(int i = 0;i<N;++i) {
            for(int j = 0;j<N;++j) {
                a[i][j] = tmp[i][j];
            }
        }
        return *this;
    }
    matrix operator*(const matrix& o) const {
        matrix ans;
        for(int k = 0;k<N;++k) {
            for(int i = 0;i<N;++i) {
                for(int j = 0;j<N;++j) {
                    ans.a[i][j] += a[i][k] * o.a[k][j];
                }
            }
        }
        return ans;
    }
    matrix operator+(const matrix& o) const {
        matrix ans;
        for(int i = 0;i<N;++i) {
            for(int j = 0;j<N;++j) {
                ans.a[i][j] = a[i][j] + o.a[i][j];
            }
        }
        return ans;
    }
    matrix& operator+=(matrix& o) {
        for(int i = 0;i<N;++i) {
            for(int j = 0;j<N;++j) {
                a[i][j] += o.a[i][j];
            }
        }
        return *this;
    }
    matrix& operator*=(matrix& o) {
        *this = o * *this;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, matrix const& mat) { 
        os << '[';
        for(int i = 0;i<N;++i) {
            os << '[';
            for(int j = 0;j<N;++j) {
                os << mat.a[i][j];
                if(j != n - 1) os << ", ";
            }
            os << ']';
        }
        os << ']';
        return os;
    }
    array<T, N>& operator[](int i) { return a[i]; }
};
