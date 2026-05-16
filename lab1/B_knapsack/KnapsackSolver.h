/*
 * Author: Bashar Al-Saify
 */

#ifndef KNAPSACK_SOLVER_H
#define KNAPSACK_SOLVER_H

#include <vector>
#include <iostream>

using namespace std;

struct Item {
    int v; // value of the item
    int w; // weight of the item
    int id; // original index to track the item
};

struct Solution {
    int maxVal; // maximum value achievable
    vector<int> indices; // Optimal solution
};

/*
 * Separates the algorithm from input/output.
 */
class KnapsackSolver {
public:
    /*
     * Params:
     *   C: The maximum capacity of the knapsack (assumed non-negative).
     *   items: A vector of Item structures (passed by reference).
     *
     * Returns:
     *   A Solution struct containing the max value and the list of item indices.
     */
    Solution solve(int C, vector<Item>& items);
};

#endif
