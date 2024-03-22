/*
 * Author: Andy Zhu
 * @date    2024-03-21 21:18:22
 * @version 1.0.0
 */

template <typename T>
T exgcd(T a, T b, T& x, T& y) {
    if((long long)a * b == 0) {
        x = 1, y = 0;
        return a + b;
    }
    T GCD = exgcd(b, a % b, x, y);
    T tmp = y;
    y = x - a / b * y;
    x = tmp;
    return GCD;
}
