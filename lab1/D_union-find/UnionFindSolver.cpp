/*
 * Author: Bashar Al-Saify
 */

#include "UnionFindSolver.h"

UnionFind::UnionFind(int n) {
    if (n < 0) {
        throw std::invalid_argument("Number of elements cannot be negative.");
    }
    parent.resize(n);
    rank.assign(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int UnionFind::find(int i) {
    if (i < 0 || i >= parent.size()) {
        throw std::out_of_range("Element index is out of bounds.");
    }
    
    // Iterative find to avoid call stack overhead
    int root = i;
    while (root != parent[root]) {
        root = parent[root];
    }
    
    // Path compression
    int curr = i;
    while (curr != root) {
        int nxt = parent[curr];
        parent[curr] = root;
        curr = nxt;
    }
    
    return root;
}

void UnionFind::unionSet(int i, int j) {
    // find() already handles boundary checking
    int rootI = find(i);
    int rootJ = find(j);
    
    // If they are in the same set, do nothing
    if (rootI != rootJ) {
        // Union by rank
        if (rank[rootI] < rank[rootJ]) {
            parent[rootI] = rootJ;
        } else if (rank[rootI] > rank[rootJ]) {
            parent[rootJ] = rootI;
        } else {
            parent[rootJ] = rootI;
            rank[rootI]++;
        }
    }
}

bool UnionFind::isSameSet(int i, int j) {
    // find() already handles boundary checking
    return find(i) == find(j);
}
