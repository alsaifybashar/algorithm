/*
 * Author: Bashar Al-Saify
 *
 * Problem:
 * Solves the Union-Find problem by reading operations from stdin and
 * printing the query answers to stdout.
 *
 * Algorithm:
 * 1. Initialize a UnionFind structure with N elements.
 * 2. Process Q operations.
 * 3. For '=' operations, join the sets containing elements 'a' and 'b'.
 * 4. For '?' operations, check if elements 'a' and 'b' belong to the same set and print "yes" or "no".
 *
 * Usage:
 *   Compile:  g++ main.cpp UnionFindSolver.cpp
 *   Run:  ./a.out < sample.in
 *
 * Time Complexity: O(Q * alpha(N)) where alpha is the inverse Ackermann function.
 */

#include <iostream>
#include <string>
#include "UnionFindSolver.h"

using namespace std;

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    while (cin >> N >> Q) {
        try {
            UnionFind uf(N);
            
            for (int i = 0; i < Q; i++) {
                char op;
                int a, b;
                cin >> op >> a >> b;
                
                if (op == '=') {
                    uf.unionSet(a, b);
                } else if (op == '?') {
                    if (uf.isSameSet(a, b)) {
                        cout << "yes\n";
                    } else {
                        cout << "no\n";
                    }
                }
            }
        } catch (const std::exception& e) {
            cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    }

    return 0;
}
