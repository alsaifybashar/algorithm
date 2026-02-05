/*
 * Author: Bashar Al-Saify
 *-------------------------
 * Algorithm:
 *   We use a Greedy approach with a Min-Heap (Priority Queue).
 *   1. Count the frequency (degree) of each node in the input list 'v'.
 *   2. Identify initial leaves (nodes 1 to n+1 with frequency 0) and push them into a min-heap.
 *   3. Iterate through the input list 'v':
 *      a. Extract the smallest leaf 'u' from the heap (this corresponds to the current step's removed leaf).
 *      b. Decrement the frequency of the current neighbor 'v[i]'.
 *      c. If 'v[i]' frequency becomes 0, it becomes a leaf, so push it into the heap.
 *   4. Check validity: The last node remaining must always be n+1. If not, output "Error".
 *
 * Time Complexity:
 *   O(N log N) - We process N elements, and each heap insertion/deletion takes O(log N).
 *-------------------------
 * Space Complexity:
 *   O(N) - To store the frequency map, priority queue, and the input/output vectors.
 *-------------------------
 * Usage Instructions:
 *   - Compile: g++ -O3 main.cpp chopping_wood.cpp 
 *   - Run: ./a.out < input_file
 *-------------------------
 */



#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "chopping_wood.hpp"
using namespace std;

int main() {

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<int> v;
    v.reserve(n);
    int input_val;
    for (int i = 0; i < n; ++i) {
        cin >> input_val;
        v.push_back(input_val);
    }

    ChoppingWoodSolver solver;
    optional<vector<int>> result = solver.solve(n, v);

    if (result.has_value()) {
        ostringstream oss;
        const vector<int>& u = result.value();
        for (int i = 0; i < n; ++i) {
            oss << u[i] << "\n";
        }
        cout << oss.str();
    } else {
        cout << "Error" << "\n";
    }

    return 0;
}
