/*
 * Author: Bashar Al-Saify
 *-------------------------
 * Problem:
 *   Given a target interval [target_start, target_end] and a set of n intervals, find a minimal
 *   set of the intervals that covers [target_start, target_end].
 *
 * Algorithm:
 *   1. Sort all intervals by their start time.
 *   2. Maintain `current_reach` (initially target_start).
 *   3. Iteratively choose the interval that starts <= `current_reach`
 *      and extends the coverage the furthest.
 *   4. Repeat until target_end is covered or impossible.
 *
 * Time Complexity:
 *   O(N log N) per test case (Sorting).
 *   Processing is O(N).
 *
 *-------------------------
 * Usage:
 *   Compile:  g++ main.cc interval_cover.cc 
 *   Run:      ./a.out < sample_input.txt
 *-------------------------
 */

#include <iostream>
#include <vector>
#include "interval_cover.h"

using namespace std;

int main() {

    double target_start, target_end;

    while (cin >> target_start >> target_end) {
        int num_intervals;
        cin >> num_intervals;
        // Optimization: if impossible to cover even with 1 interval (empty input), handle gracefully
        // Though problem says 1 <= n <= 20000.
        
        vector<Interval> candidates(num_intervals);
        for (int i = 0; i < num_intervals; ++i) {
            cin >> candidates[i].start >> candidates[i].end;
            candidates[i].index = i;
        }

        vector<int> result = solve_interval_cover(target_start, target_end, candidates);

        if (result.empty()) {
            cout << "impossible" << endl;
        } else {
            cout << result.size() << endl;
            for (size_t i = 0; i < result.size(); ++i) {
                cout << result[i] << (i == result.size() - 1 ? "" : " ");
            }
            cout << endl;
        }
    }
    return 0;
}
