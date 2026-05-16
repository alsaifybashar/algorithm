/*
 * Author: Bashar Al-Saify
 *
 * PolynomialMultiplier.cpp
 *
 * Implementation of FFT-based polynomial multiplication.
 *
 * Algorithm (Cooley-Tukey iterative FFT):
 *   1. Pad both coefficient arrays with zeros to a combined length that is the
 *      next power of 2 (to allow in-place bit-reversal FFT).
 *   2. Convert both real coefficient arrays into complex<double> arrays.
 *   3. Run the forward FFT on each array, transforming them into the frequency
 *      (point-value) domain.
 *   4. Multiply the two arrays element-wise in the frequency domain.
 *      (Polynomial multiplication = convolution, which is point-wise product
 *       in the frequency domain.)
 *   5. Run the inverse FFT on the product array to get back the coefficient
 *      representation.
 *   6. Round each complex result to the nearest integer (to correct for
 *      floating-point rounding errors) and store as long long.
 *
 * Time Complexity:  O(n log n) where n is the padded size.
 * Memory Complexity: O(n) additional for the complex working arrays.
 */

#include "PolynomialMultiplier.h"
#include <cmath>

// Pi constant used for computing FFT twiddle factors.
static const double PI = acos(-1.0);

/*
 * Returns the smallest power of 2 that is >= n.
 * We use this to find the correct FFT size.
 */
int PolynomialMultiplier::nextPowerOfTwo(int n) {
    int power = 1;
    while (power < n) {
        power = power * 2;
    }
    return power;
}

/*
 * Iterative Cooley-Tukey FFT.
 *
 * Steps:
 *   1. Bit-reversal permutation: rearrange elements so that the recursive
 *      divide-and-conquer structure is unrolled bottom-up without recursion.
 *   2. Butterfly passes: repeatedly combine pairs of elements using twiddle
 *      factors (roots of unity). Each pass doubles the "stride" until the
 *      full transform is computed.
 *   3. If invert is true, divide every element by n to complete the IFFT.
 */
void PolynomialMultiplier::fft(vector<complex<double>>& a, bool invert) {
    int n = a.size();

    // Swap element at position i with element at its bit-reversed position.
    // This reorders the array so bottom-up butterfly passes work correctly.
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }

    // --- Butterfly passes ---
    // len doubles each pass: 2, 4, 8, ..., n.
    for (int len = 2; len <= n; len <<= 1) {
        // For forward FFT: w = e^(2*pi*i / len)
        // For inverse FFT: w = e^(-2*pi*i / len)
        double angle = 2.0 * PI / len;
        if (invert) {
            angle = -angle;
        }
        complex<double> wlen(cos(angle), sin(angle));

        // Process each block of size len in the array.
        for (int i = 0; i < n; i += len) {
            complex<double> w(1.0, 0.0); // current twiddle factor, starts at 1

            // Apply butterfly to each pair within the block.
            for (int j = 0; j < len / 2; j++) {
                complex<double> u = a[i + j];
                complex<double> v = a[i + j + len / 2] * w;

                // Combine: upper half gets u + v, lower half gets u - v.
                a[i + j]           = u + v;
                a[i + j + len / 2] = u - v;

                w = w * wlen;
            }
        }
    }

    
    if (invert) {
        for (int i = 0; i < n; i++) {
            a[i] = a[i] / (double)n;
        }
    }
}

/*
 * Multiplies polyA and polyB using FFT-based convolution.
 *
 * The result has degree = deg(A) + deg(B), so the result vector has
 * polyA.size() + polyB.size() - 1 entries.
 */
vector<long long> PolynomialMultiplier::multiply(const vector<long long>& polyA,
                                                  const vector<long long>& polyB) {
    // The result polynomial needs this many coefficients.
    int resultSize = (int)(polyA.size() + polyB.size() - 1);

    // FFT requires a size that is a power of 2 (and >= resultSize).
    int fftSize = nextPowerOfTwo(resultSize);

    // Load polyA and polyB into complex arrays, zero-padded to fftSize.
    vector<complex<double>> fa(fftSize, {0.0, 0.0});
    vector<complex<double>> fb(fftSize, {0.0, 0.0});

    for (int i = 0; i < (int)polyA.size(); i++) {
        fa[i] = {(double)polyA[i], 0.0};
    }
    for (int i = 0; i < (int)polyB.size(); i++) {
        fb[i] = {(double)polyB[i], 0.0};
    }

    // Transform both polynomials into the frequency domain.
    fft(fa, false);
    fft(fb, false);

    // Point-wise multiplication in frequency domain = convolution in time domain.
    for (int i = 0; i < fftSize; i++) {
        fa[i] = fa[i] * fb[i];
    }

    // Transform back to coefficient domain.
    fft(fa, true);

    // Round floating-point results to integers and build the result vector.
    vector<long long> result(resultSize);
    for (int i = 0; i < resultSize; i++) {
        result[i] = llround(fa[i].real());
    }

    return result;
}
