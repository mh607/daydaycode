#include <iostream>

double myPow(double x, int n) {
    if(x == 0.0f) return 0.0;
    long b = n;
    double res = 1.0;
    if(b < 0) {
        x = 1 / x;
        b = -b;
    }
    while(b > 0) {
       if((b & 1) == 1) res *= x;
        x *= x;
        b >>= 1;
    }
    return res;
}

int main() {
    std::cout << myPow(2.00000, 10) << std::endl;
    std::cout << std::endl;
    return 0;
}
