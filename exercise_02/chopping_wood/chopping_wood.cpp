#include "chopping_wood.hpp"
#include <vector>
#include <queue>
#include <map>
#include <functional>
using namespace std;

optional<vector<int>> ChoppingWoodSolver::solve(int n, const vector<int>& v) {
    // Basic validation: 
    if (v.empty() || v.back() != n + 1) {
        return nullopt;
    }

    // Frequency map to count occurrences of each node in v
    map<int, int> counts;
    for (int x : v) {
        counts[x]++;
    }

    // Priority queue to store available leaves (min-heap)
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n + 1; ++i) {
        if (counts.find(i) == counts.end()) {
            pq.push(i);
        }
    }

    vector<int> u_list;
    u_list.reserve(n);

    for (int x : v) {
    
        // Get the smallest leaf
        int leaf = pq.top();
        pq.pop();
        u_list.push_back(leaf);

        // Process the neighbor 'x'
        counts[x]--;
        if (counts[x] == 0) {
            // If count becomes 0, it means 'x' has become a leaf (no other edges connecting to it in the remaining list)
            // It is now available to be chopped in future steps.
            pq.push(x);
        }
    }

    return u_list;
}
