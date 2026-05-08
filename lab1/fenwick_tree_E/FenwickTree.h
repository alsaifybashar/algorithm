/*
 * Author: Bashar Al-Saify
 *
 * Problem:
 * This file provides the definition for a Fenwick Tree (Binary Indexed Tree).
 * It supports efficiently updating elements and calculating prefix sums in an array.
 *
 * Algorithm:
 * A Fenwick Tree implicitly represents an array of numbers and their partial sums.
 * It uses the binary representation of indices to determine which ranges of elements
 * are stored at each node. Specifically, the element at index `i` (1-based) stores
 * the sum of the range `(i - (i & -i), i]`.
 * 
 * Time Complexity:
 * - constructor: O(N) where N is the number of elements.
 * - add: O(log N) worst-case time to update an element.
 * - query: O(log N) worst-case time to compute the prefix sum.
 *
 * Memory Complexity:
 * - O(N) auxiliary space, specifically an array of size N + 1 using 8-byte integers.
 */

#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

#include <vector>
#include <stdexcept>

class FenwickTree {
private:
    int size;
    std::vector<long long> tree;

public:
    /*
     * Constructor
     * Initializes a Fenwick Tree with `n` elements, all initially 0.
     * 
     * Parameters:
     *   n - The number of elements in the array.
     * 
     * Exceptions:
     *   Throws std::invalid_argument if n is negative.
     */
    explicit FenwickTree(int n);

    /*
     * add
     * Increments the element at the specified 0-based index by a given delta.
     * 
     * Parameters:
     *   index - The 0-based index of the element to update (0 <= index < n).
     *   delta - The value to add to the element.
     * 
     * Exceptions:
     *   Throws std::out_of_range if `index` is less than 0 or greater than or equal to n.
     */
    void add(int index, long long delta);

    /*
     * query
     * Calculates the sum of the first `count` elements in the array (prefix sum).
     * Specifically, returns a[0] + a[1] + ... + a[count - 1].
     * 
     * Parameters:
     *   count - The number of elements to sum (0 <= count <= n).
     * 
     * Exceptions:
     *   Throws std::out_of_range if `count` is less than 0 or greater than n.
     */
    long long query(int count) const;
};

#endif
