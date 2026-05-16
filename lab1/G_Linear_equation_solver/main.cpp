/*
 * Author: Bashar Al-Saify
 *
 * Problem:
 * Reads multiple systems of linear equations (Ax = b) from stdin and for each
 * one prints either the unique solution vector x, "multiple" (if infinitely many
 * solutions exist), or "inconsistent" (if no solution exists).
 *
 * Algorithm:
 * Uses Gaussian elimination with partial pivoting to reduce the augmented matrix
 * [A | b] to row echelon form, then applies back-substitution to find x.
 * Partial pivoting improves numerical stability by always choosing the largest
 * available entry as the pivot at each step.
 *
 * Usage:
 *   Compile:  g++ main.cpp LinearSolver.cpp
 *   Run:      ./a.out < sample.in
 *
 * Time Complexity: O(n^3) per test case, where n is the number of equations.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include "LinearSolver.h"

using namespace std;

int main() {
    int n;

    // Keep reading test cases until n = 0 (the termination sentinel).
    while (cin >> n && n != 0) {

        // Read the n x n matrix A.
        vector<vector<double>> A(n, vector<double>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> A[i][j];
            }
        }

        // Read the right-hand side vector b.
        vector<double> b(n);
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        // Delegate to the solver (keeps I/O separate from algorithm).
        LinearSolver solver;
        SolveResult result = solver.solve(A, b);

        if (result.status == SolveStatus::INCONSISTENT) {
            cout << "inconsistent\n";
        } else if (result.status == SolveStatus::MULTIPLE) {
            cout << "multiple\n";
        } else {
            // Print each solution value separated by spaces.
            // The problem allows error up to 10^-3, so 9 decimal places is safe.
            for (int i = 0; i < n; i++) {
                if (i > 0) {
                    cout << " ";
                }
                // Use enough precision to stay within the allowed 10^-3 error.
                cout << fixed << setprecision(9) << result.x[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
