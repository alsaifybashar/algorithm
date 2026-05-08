/*
 * Author: Bashar Al-Saify
 *
 * Problem:
 * Solves the Fenwick Tree (Binary Indexed Tree) problem by reading operations
 * from stdin and printing the query answers to stdout.
 *
 * Algorithm:
 * 1. Initialize a FenwickTree structure with N elements.
 * 2. Process Q operations in a loop.
 * 3. For '+' operations, read index and delta, and add delta to the array at the given index.
 * 4. For '?' operations, read index and query the prefix sum up to that index, then print it.
 *
 * Usage:
 *   Compile:  g++ -O3 main.cpp FenwickTree.cpp -o fenwick
 *   Run:  ./fenwick < sample.in
 *
 * Time Complexity: O(Q * log N) worst-case processing time.
 */

#include <iostream>
#include "FenwickTree.h"

using namespace std;

int main() {
    // Optimize standard I/O operations for performance
    // This is strictly necessary for large inputs like Q=5,000,000
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    if (cin >> N >> Q) {
        try {
            FenwickTree ft(N);
            
            for (int k = 0; k < Q; k++) {
                char op;
                cin >> op;
                
                if (op == '+') {
                    int i;
                    long long delta;
                    cin >> i >> delta;
                    ft.add(i, delta);
                } else if (op == '?') {
                    int i;
                    cin >> i;
                    cout << ft.query(i) << "\n";
                }
            }
        } catch (const std::exception& e) {
            cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    }

    return 0;
}
