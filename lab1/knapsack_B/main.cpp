/*
 * Author: Bashar Al-Saify
 *
 * Problem:
 * Solves the Knapsack 0/1 problem by reading input from stdin and
 * printing the solution to stdout.
 *
 * Algorithm:
 * 1. Create a 1D array `dp[w]` that stores the max value for each capacity w.
 * 2. For each item, iterate capacity from C down to the items weight:
 *      - If including the item gives better value, update dp[w].
 * 3. The optimal value is found at `dp[C]`.
 * 4. Backtrack using a tracking table to identify selected items.
 *
 * Usage:
 *   Compile:  g++ main.cpp KnapsackSolver.cpp
 *   Run:  ./a.out < sample_input.in
 *
 * Time Complexity: O(n * C) where n is the number of items and C is the capacity.
 */

#include <iostream>
#include <vector>
#include "KnapsackSolver.h"

using namespace std;

int main() {
    int C, n;
    
    while (cin >> C >> n) {
        vector<Item> items;
        
        // Read n items
        for (int i = 0; i < n; i++) {
            int v, w;
            cin >> v >> w;
            
            // Create item object and store it
            Item newItem;
            newItem.v = v;
            newItem.w = w;
            newItem.id = i; // Store original index (0-based)
            items.push_back(newItem);
        }

        // Create solver instance and solve the problem
        KnapsackSolver solver;
        Solution s = solver.solve(C, items);

        cout << s.indices.size() << "\n";
        
        for (int i = 0; i < s.indices.size(); i++) {
            cout << s.indices[i];
            if (i < s.indices.size() - 1) {
                cout << " ";
            }
        }
        cout << "\n";
    }
    
    // Flush the output buffer once at the end.
    cout << flush;

    return 0;
}
