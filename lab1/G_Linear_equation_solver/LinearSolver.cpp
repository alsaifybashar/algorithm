/*
 * Author: Bashar Al-Saify
 *
 * LinearSolver.cpp
 *
 * Implementation of Gaussian elimination with partial pivoting.
 *
 * Algorithm overview:
 *   1. Build an augmented matrix [A | b] of size n x (n+1).
 *   2. Forward elimination: for each column (pivot column), find the row
 *      with the largest absolute value in that column at or below the current
 *      diagonal (partial pivoting), swap it to the pivot row, then eliminate
 *      all entries below the pivot by subtracting a scaled version of the
 *      pivot row.
 *   3. After elimination, check the diagonal:
 *       - If a diagonal entry is effectively zero but the corresponding
 *         right-hand side is non-zero, the system is INCONSISTENT.
 *       - If a diagonal entry is effectively zero and the right-hand side is
 *         also zero, the system has free variables -> MULTIPLE solutions.
 *   4. If the system is UNIQUE, perform back-substitution to recover x.
 *
 * Time Complexity:  O(n^3)
 * Memory Complexity: O(n^2) for the augmented matrix.
 */

#include "LinearSolver.h"
#include <cmath>

// Values smaller than this threshold are treated as zero to handle
// floating-point rounding errors near true zero.
static const double EPSILON = 1e-9;

SolveResult LinearSolver::solve(vector<vector<double>> A, vector<double> b) {
    int n = (int)A.size();

    // Build the augmented matrix [A | b].
    // Each row has n+1 entries: the n coefficients followed by the rhs value.
    vector<vector<double>> aug(n, vector<double>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug[i][j] = A[i][j];
        }
        aug[i][n] = b[i];
    }

    // --- Forward Elimination with Partial Pivoting ---
    // col tracks which column we are currently eliminating.
    // pivotRow tracks which row should receive the next pivot.
    int pivotRow = 0;
    for (int col = 0; col < n && pivotRow < n; col++) {

        // Find the row with the largest absolute value in this column,
        // starting from pivotRow. This is partial pivoting.
        int bestRow = pivotRow;
        double bestVal = fabs(aug[pivotRow][col]);
        for (int row = pivotRow + 1; row < n; row++) {
            if (fabs(aug[row][col]) > bestVal) {
                bestVal = fabs(aug[row][col]);
                bestRow = row;
            }
        }

        // If the best value found is essentially zero, this column has no
        // usable pivot (all entries are zero). Skip to the next column.
        // This happens when a variable is free (underdetermined system).
        if (fabs(aug[bestRow][col]) < EPSILON) {
            continue;
        }

        // Swap the best row into the pivot position.
        swap(aug[pivotRow], aug[bestRow]);

        // Eliminate entries below the pivot in this column.
        for (int row = pivotRow + 1; row < n; row++) {
            double factor = aug[row][col] / aug[pivotRow][col];
            for (int k = col; k <= n; k++) {
                aug[row][k] -= factor * aug[pivotRow][k];
            }
        }

        pivotRow++;
    }

    // --- Check for Inconsistency or Multiple Solutions ---
    // After elimination, examine rows that have no pivot (all-zero coefficient part).
    for (int i = pivotRow; i < n; i++) {
        // Check if any remaining row has a non-zero rhs, which means no solution.
        if (fabs(aug[i][n]) > EPSILON) {
            SolveResult result;
            result.status = SolveStatus::INCONSISTENT;
            return result;
        }
    }

    // If pivotRow < n, we have fewer pivots than unknowns, so there are free
    // variables and infinitely many solutions.
    if (pivotRow < n) {
        SolveResult result;
        result.status = SolveStatus::MULTIPLE;
        return result;
    }

    // --- Back Substitution ---
    // At this point, the augmented matrix is in row echelon form with n pivots,
    // so there is exactly one solution. Solve from the bottom row upward.
    vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        // Find which column the pivot of row i is in.
        // In a square system with n pivots, the pivot of row i is at column i.
        double sum = aug[i][n];
        for (int j = i + 1; j < n; j++) {
            sum -= aug[i][j] * x[j];
        }
        x[i] = sum / aug[i][i];
    }

    SolveResult result;
    result.status = SolveStatus::UNIQUE;
    result.x = x;
    return result;
}
