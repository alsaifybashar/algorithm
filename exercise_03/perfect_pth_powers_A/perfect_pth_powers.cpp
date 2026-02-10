#include "perfect_pth_powers.hpp"
#include <algorithm>
using namespace std;

// Returns the GCD of two non-negative integers.
static int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int PerfectPthPowersSolver::solve(long long x) {
    bool negative = (x < 0);
    if (negative) x = -x;

    // Factorise |x| by trial division; track GCD of all exponents.
    int exponent_gcd = 0;

    // Check factor 2
    if (x % 2 == 0) {
        int current_exponent = 0;
        while (x % 2 == 0) { x /= 2; current_exponent++; }
        exponent_gcd = current_exponent;
    }

    // Check odd factors up to sqrt(x)
    for (long long factor = 3; factor * factor <= x; factor += 2) {
        if (x % factor == 0) {
            int current_exponent = 0;
            while (x % factor == 0) { x /= factor; current_exponent++; }
            exponent_gcd = gcd(exponent_gcd, current_exponent);
        }
    }

    // If x > 1 after the loop, x itself is a prime factor with exponent 1
    if (x > 1) {
        exponent_gcd = gcd(exponent_gcd, 1);
    }

    // For negative input only odd exponents are valid.
    // Find the largest odd divisor of exponent_gcd.
    if (negative) {
        while (exponent_gcd % 2 == 0) exponent_gcd /= 2;
    }

    return exponent_gcd;
}
