#ifndef CHOPPING_WOOD_HPP
#define CHOPPING_WOOD_HPP

#include <vector>
#include <optional>
using namespace std;


class ChoppingWoodSolver {
public:
    /**
     * @brief Solves the tree reconstruction problem.
     * 
     * 
     * @param n The number of steps (length of the v sequence).
     * @param v The sequence of neighbor vertices.
     * @return optional<vector<int>> The sequence of removed leaves if a valid tree exists,
     *         or nullopt if the sequence is invalid.
     * 
     * @note Time Complexity: O(N log N) due to priority queue operations.
     * @note Space Complexity: O(N) to store counts and the tree structure.
     */
    optional<vector<int>> solve(int n, const vector<int>& v);
};

#endif
