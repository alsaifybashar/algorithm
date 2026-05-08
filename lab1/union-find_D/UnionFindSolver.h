/*
 * Author: Bashar Al-Saify
 *
 * Problem:
 * This file provides the definition for a Disjoint-Set Data Structure (Union-Find).
 * It solves the problem of efficiently keeping track of a set of elements partitioned
 * into a number of disjoint (non-overlapping) subsets.
 *
 * Algorithm:
 * Uses a tree-based representation with two key optimizations:
 * - Path Compression (in the find operation) to flatten the structure of the tree.
 * - Union by Rank (in the union operation) to always attach the smaller tree to the root of the larger tree.
 *
 * Time Complexity:
 * - constructor: O(N)
 * - find: O(alpha(N)) 
 * - unionSet: O(alpha(N)) 
 * - isSameSet: O(alpha(N))
 * where alpha(N) is the inverse Ackermann function, which grows extremely slowly.
 */

#ifndef UNION_FIND_SOLVER_H
#define UNION_FIND_SOLVER_H

#include <vector>
#include <stdexcept>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    /*
     * Constructor
     * Initializes a UnionFind structure with n disjoint sets.
     * 
     * Parameters:
     *   n - The number of elements. Elements will be 0-indexed up to n-1.
     * 
     * Exceptions:
     *   Throws std::invalid_argument if n is negative.
     */
    explicit UnionFind(int n);

    /*
     * find
     * Returns the representative (root) of the set that element 'i' belongs to.
     * Applies path compression to optimize future queries.
     * 
     * Parameters:
     *   i - The element to find the root for.
     * 
     * Exceptions:
     *   Throws std::out_of_range if 'i' is not between 0 and n-1.
     */
    int find(int i);

    /*
     * unionSet
     * Merges the sets containing elements 'i' and 'j'.
     * Uses union by rank for efficiency.
     * 
     * Parameters:
     *   i, j - The elements whose sets are to be merged.
     * 
     * Exceptions:
     *   Throws std::out_of_range if 'i' or 'j' are not between 0 and n-1.
     */
    void unionSet(int i, int j);

    /*
     * isSameSet
     * Checks whether elements 'i' and 'j' belong to the same set.
     * 
     * Parameters:
     *   i, j - The elements to check.
     * 
     * Exceptions:
     *   Throws std::out_of_range if 'i' or 'j' are not between 0 and n-1.
     */
    bool isSameSet(int i, int j);
};

#endif
