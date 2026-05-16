/*
 * Author: Bashar Al-Saify
 *
 * PolynomialMultiplier.h
 *
 * Declares the PolynomialMultiplier class which multiplies two polynomials
 * using the Fast Fourier Transform (FFT) in O(n log n) time.
 *
 * A polynomial is represented as a vector<long long> where the element at
 * index i is the coefficient of x^i.
 *
 * Usage:
 *   PolynomialMultiplier pm;
 *   vector<long long> result = pm.multiply(polyA, polyB);
 *
 * Assumptions:
 *   - Both input vectors are non-empty.
 *   - Coefficients fit in a signed 32-bit integer (per problem statement),
 *     but intermediate products are accumulated as long long to avoid overflow.
 *   - The result coefficients are guaranteed to fit in a signed 32-bit integer
 *     (per problem statement), so final rounding is safe.
 */

#ifndef POLYNOMIAL_MULTIPLIER_H
#define POLYNOMIAL_MULTIPLIER_H

#include <vector>
#include <complex>

using namespace std;

class PolynomialMultiplier {
public:
    /*
     * Multiplies two polynomials represented as coefficient vectors.
     *
     * Params:
     *   polyA: Coefficients of the first polynomial (index i = coefficient of x^i).
     *          Assumed non-empty.
     *   polyB: Coefficients of the second polynomial (index i = coefficient of x^i).
     *          Assumed non-empty.
     *
     * Returns:
     *   A vector<long long> of size (polyA.size() + polyB.size() - 1) holding the
     *   coefficients of the product polynomial.
     *
     * Time Complexity:  O(n log n) where n = deg(A) + deg(B) + 1.
     * Memory Complexity: O(n) additional memory for the working arrays.
     */
    vector<long long> multiply(const vector<long long>& polyA,
                               const vector<long long>& polyB);

private:
    /*
     * Performs the Cooley-Tukey iterative FFT (or its inverse) in-place.
     *
     * Params:
     *   a:       The complex-valued array to transform (length must be a power of 2).
     *   invert:  If true, computes the inverse FFT; otherwise the forward FFT.
     *
     * Time Complexity:  O(n log n).
     */
    void fft(vector<complex<double>>& a, bool invert);

    /*
     * Returns the smallest power of 2 that is >= n.
     *
     * Params:
     *   n: A positive integer.
     *
     * Returns: The next power of 2 >= n.
     */
    int nextPowerOfTwo(int n);
};

#endif
