/*
 * Author: Bashar Al-Saify
 */

#include "LISSolver.h"
#include <algorithm>

Solution LISSolver::solve(const vector<int>& sequence) {
    int n = sequence.size();
    if (n == 0) {
        return {0, {}};
    }

    // tails[i] stores the smallest tail of all increasing subsequences of length i+1.
    vector<int> tails;
    // tailIndices[i] stores the original index of the element tails[i].
    vector<int> tailIndices;
    // parent[i] stores the index of the predecessor of sequence[i] in the LIS.
    vector<int> parent(n, -1);

    for (int i = 0; i < n; i++) {
        // Find the index of the first element in tails that is >= sequence[i]
        auto it = lower_bound(tails.begin(), tails.end(), sequence[i]);
        int pos = distance(tails.begin(), it);

        if (it == tails.end()) {
            tails.push_back(sequence[i]);
            tailIndices.push_back(i);
        } else {
            *it = sequence[i];
            tailIndices[pos] = i;
        }

        if (pos > 0) {
            parent[i] = tailIndices[pos - 1];
        }
    }

    Solution sol;
    sol.length = tails.size();

    // Backtrack to find the indices
    int curr = tailIndices.back();
    while (curr != -1) {
        sol.indices.push_back(curr);
        curr = parent[curr];
    }
    
    // Reverse the indices to get them in ascending order
    reverse(sol.indices.begin(), sol.indices.end());

    return sol;
}
