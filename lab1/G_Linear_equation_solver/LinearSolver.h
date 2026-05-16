/*
 * Author: Bashar Al-Saify
 *
 * LinearSolver.h
 *
 * Declares the LinearSolver class, which solves a system of n linear equations
 * in n unknowns (Ax = b) using Gaussian elimination with partial pivoting.
 *
 * The solver distinguishes three outcomes:
 *   - A unique solution vector x.
 *   - Infinitely many solutions ("multiple").
 *   - No solution at all ("inconsistent").
 *
 * Usage:
 *   LinearSolver solver;
 *   SolveResult result = solver.solve(A, b);
 *   if (result.status == SolveStatus::UNIQUE) { ... }
 *
 * Assumptions:
 *   - A is an n x n matrix passed as a vector of rows, each of length n.
 *   - b is a vector of length n.
 *   - n >= 1.
 *   - The caller is responsible for correct dimensions.
 */

#ifndef LINEAR_SOLVER_H
#define LINEAR_SOLVER_H

#include <vector>
#include <string>

using namespace std;

/*
 * Describes the outcome of attempting to solve the linear system.
 */
enum class SolveStatus {
    UNIQUE,       // Exactly one solution exists
    MULTIPLE,     // Infinitely many solutions exist
    INCONSISTENT  // No solution exists
};

/*
 * Holds the result returned by LinearSolver::solve().
 *
 * Fields:
 *   status  - One of UNIQUE, MULTIPLE, or INCONSISTENT.
 *   x       - The solution vector (only meaningful when status == UNIQUE).
 */
struct SolveResult {
    SolveStatus status;
    vector<double> x;
};

class LinearSolver {
public:
    /*
     * Solves the n x n linear system Ax = b using Gaussian elimination
     * with partial pivoting.
     *
     * Partial pivoting swaps rows to place the largest available pivot on the
     * diagonal at each step. This improves numerical stability for floating-
     * point inputs.
     *
     * Params:
     *   A: The n x n coefficient matrix (rows are the equations).
     *      Passed by value so we can modify it in place during elimination.
     *   b: The right-hand side vector of length n.
     *      Also passed by value so it can be modified alongside A.
     *
     * Returns:
     *   A SolveResult struct with the status and (if unique) the solution vector.
     *
     * Time Complexity:  O(n^3) for the forward elimination and back-substitution.
     * Memory Complexity: O(n^2) for the augmented matrix copy (same as input).
     */
    SolveResult solve(vector<vector<double>> A, vector<double> b);
};

#endif
