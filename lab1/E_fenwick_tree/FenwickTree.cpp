/*
 * Author: Bashar Al-Saify
 */

#include "FenwickTree.h"

FenwickTree::FenwickTree(int n) {
    if (n < 0) {
        throw std::invalid_argument("Size of Fenwick Tree cannot be negative.");
    }
    size = n;
    // We use 1-based indexing internally, so we need size + 1
    tree.assign(size + 1, 0LL);
}

void FenwickTree::add(int index, long long delta) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds for Fenwick Tree update.");
    }
    
    // Convert to 1-based index
    int i = index + 1;
    while (i <= size) {
        tree[i] += delta;
        i += (i & -i); // Add the lowest set bit
    }
}

long long FenwickTree::query(int count) const {
    if (count < 0 || count > size) {
        throw std::out_of_range("Count out of bounds for Fenwick Tree query.");
    }
    
    long long sum = 0;
    // count naturally acts as our 1-based index for the prefix sum
    int i = count;
    while (i > 0) {
        sum += tree[i];
        i -= (i & -i); // Subtract the lowest set bit
    }
    
    return sum;
}
