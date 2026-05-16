/*
 * Author: Bashar Al-Saify
 */

#ifndef LIS_SOLVER_H
#define LIS_SOLVER_H

#include <vector>
#include <iostream>

using namespace std;

struct Solution {
    int length; // length of LIS
    vector<int> indices; // Optimal solution
};

/*
 * Separates the algorithm from input/output.
 */
class LISSolver {
public:
    /*
     * Params:
     *   sequence: A vector of integers representing the sequence.
     *
     * Returns:
     *   A Solution struct containing the length of LIS and the list of item indices.
     */
    Solution solve(const vector<int>& sequence);
};

#endif
