/*
 * Author: Bashar Al-Saify
 *
 * Problem:
 * Solves the Longest Increasing Subsequence problem by reading input from stdin and
 * printing the solution to stdout.
 *
 * Algorithm:
 * 1. Maintain an array `tails` where `tails[i]` stores the smallest tail of all
 *    increasing subsequences of length i+1.
 * 2. Maintain `tailIndices` to keep track of the original indices of the elements in `tails`.
 * 3. Maintain a `parent` array to backtrack and reconstruct the optimal sequence.
 * 4. Iterate through the sequence. For each element, use binary search (`lower_bound`)
 *    to find its position in `tails`. Update `tails`, `tailIndices`, and `parent`.
 * 5. Reconstruct the sequence by backtracking from the last element added to `tailIndices`.
 *
 * Usage:
 *   Compile:  g++ main.cpp LISSolver.cpp
 *   Run:  ./a.out < sample.in
 *
 * Time Complexity: O(n log n) where n is the length of the sequence.
 */

#include <iostream>
#include <vector>
#include "LISSolver.h"

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    
    while (cin >> n) {
        vector<int> sequence(n);
        
        // Read sequence
        for (int i = 0; i < n; i++) {
            cin >> sequence[i];
        }

        // Create solver instance and solve the problem
        LISSolver solver;
        Solution s = solver.solve(sequence);

        cout << s.length << "\n";
        
        for (int i = 0; i < s.indices.size(); i++) {
            cout << s.indices[i];
            if (i < s.indices.size() - 1) {
                cout << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
