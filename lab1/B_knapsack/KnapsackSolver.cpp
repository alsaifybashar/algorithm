/*
 * Author: Bashar Al-Saify
 */

#include "KnapsackSolver.h"

Solution KnapsackSolver::solve(int C, vector<Item>& items) {
    int n = items.size();
    
    // 1D dp array - dp[w] stores max value for capacity w
    vector<int> dp(C + 1, 0);
    
    // Track which items were taken so we can find the solution later
    vector<vector<bool>> took(n, vector<bool>(C + 1, false));

    // Fill the DP table
    for (int i = 0; i < n; i++) {
        // Go backwards from C to item weight
        // This makes sure we dont use the same item more than once
        for (int w = C; w >= items[i].w; w--) {
            // Checks if it's a better value
            int valWith = dp[w - items[i].w] + items[i].v;
            
            if (valWith > dp[w]) {
                dp[w] = valWith;
                took[i][w] = true;
            }
        }
    }

    Solution sol;
    sol.maxVal = dp[C];
    
    // Backtrack to find which items were taken
    int currW = C;
    for (int i = n - 1; i >= 0; i--) {
        if (took[i][currW]) {
            sol.indices.push_back(items[i].id);
            currW = currW - items[i].w;
        }
    }
    
    return sol;
}
