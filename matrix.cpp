#include <array>
#include <iostream>
namespace cp {
#ifndef CP_MATRIX
#define CP_MATRIX
template <typename T, int N> class matrix {
public:
    matrix() : a{} {}
    matrix(const std::array<std::array<T, N>, N>& tmp) : a(tmp) {}

    matrix& operator+=(const matrix& o) {
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j) a[i][j] += o.a[i][j];
        return *this;
    }
    matrix& operator*=(const matrix& o) { *this = *this * o; return *this; }

    matrix operator*(const matrix& o) const {
        matrix ans;
        for(int k = 0; k < N; ++k)
            for(int i = 0; i < N; ++i)
                for(int j = 0; j < N; ++j) ans.a[i][j] += a[i][k] * o.a[k][j];
        return ans;
    }
    friend matrix operator+(matrix lhs, const matrix& rhs) { return lhs += rhs; }

    std::array<T, N>& operator[](int i) { return a[i]; }
    const std::array<T, N>& operator[](int i) const { return a[i]; }

    friend std::ostream& operator<<(std::ostream& os, const matrix& m) {
        os << '[';
        for(int i = 0; i < N; ++i) {
            os << '[';
            for(int j = 0; j < N; ++j) {
                os << m.a[i][j];
                if(j != N - 1) os << ", ";
            }
            os << ']';
        }
        return os << ']';
    }

private:
    std::array<std::array<T, N>, N> a;
};

#endif // CP_MATRIX
} // namespace cp
