/*
 * Author: Bashar Al-Saify
 *-------------------------
 * Problem:
 *   Given an integer x (|x| >= 2), find the largest integer p
 *   such that x = b^p for some integer b.
 *
 * Algorithm:
 *   1. Factorise |x| using trial division up to sqrt(|x|).
 *   2. Compute the GCD of all prime-factor exponents.
 *   3. If x is negative, only odd exponents are valid, so take
 *      the largest odd divisor of the GCD.
 *
 * Time Complexity:
 *   O(sqrt(|x|)) per test case (trial division).
 *
 *-------------------------
 * Usage:
 *   Compile:  g++ -O2 main.cpp perfect_pth_powers.cpp 
 *   Run:      ./a.out < sample_intput.in
 *-------------------------
 */

#include <iostream>
#include "perfect_pth_powers.hpp"
using namespace std;

int main() {

    PerfectPthPowersSolver solver;
    long long x;

    while (cin >> x && x != 0) {
        cout << solver.solve(x) << "\n";
    }

    return 0;
}
