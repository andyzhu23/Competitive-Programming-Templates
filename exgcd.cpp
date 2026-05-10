namespace cp {
#ifndef CP_EXGCD
#define CP_EXGCD
// Extended Euclidean: solves a*x + b*y = gcd(a, b); returns gcd(a, b).
template <typename T> T exgcd(T a, T b, T& x, T& y) {
    if((long long)a * b == 0) { x = 1; y = 0; return a + b; }
    T g = exgcd(b, a % b, x, y);
    T tmp = y;
    y = x - a / b * y;
    x = tmp;
    return g;
}
#endif // CP_EXGCD
} // namespace cp
