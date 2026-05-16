/*
 * Author: Bashar Al-Saify
 *
 * Problem:
 * Reads two polynomials from stdin and outputs their product to stdout.
 * Each polynomial is given as: degree n, then n+1 coefficients a_0..a_n.
 * The result is printed in the same format.
 *
 * Algorithm:
 * Uses FFT (Fast Fourier Transform) to compute the convolution of the two
 * coefficient arrays in O(n log n) time, where n is the total degree of the
 * result. A naive O(n^2) loop would be too slow given degrees up to 131071.
 *
 * Usage:
 *   Compile:  g++ main.cpp PolynomialMultiplier.cpp
 *   Run:      ./a.out < sample.in
 *
 * Time Complexity: O(n log n) where n = deg(A) + deg(B).
 *
 * I/O Note:
 * The problem states that input/output files are large. We use scanf/printf
 * instead of cin/cout, since they are faster for large integer I/O.
 */

#include <cstdio>
#include <vector>
#include "PolynomialMultiplier.h"

using namespace std;

int main() {
    int T;
    scanf("%d", &T);

    // Process each test case (T is always 1 per problem statement).
    for (int t = 0; t < T; t++) {
        // Read the first polynomial.
        int degA;
        scanf("%d", &degA);

        // degA is the degree, so there are degA + 1 coefficients (a_0 .. a_degA).
        vector<long long> polyA(degA + 1);
        for (int i = 0; i <= degA; i++) {
            scanf("%lld", &polyA[i]);
        }

        // Read the second polynomial.
        int degB;
        scanf("%d", &degB);

        vector<long long> polyB(degB + 1);
        for (int i = 0; i <= degB; i++) {
            scanf("%lld", &polyB[i]);
        }

        // Multiply the two polynomials using FFT-based convolution.
        PolynomialMultiplier pm;
        vector<long long> product = pm.multiply(polyA, polyB);

        // The degree of the product is degA + degB.
        int degResult = degA + degB;
        printf("%d\n", degResult);

        // Print all degResult + 1 coefficients separated by spaces.
        for (int i = 0; i <= degResult; i++) {
            if (i > 0) {
                printf(" ");
            }
            printf("%lld", product[i]);
        }
        printf("\n");
    }

    return 0;
}
