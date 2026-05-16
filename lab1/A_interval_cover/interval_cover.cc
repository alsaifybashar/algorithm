/**
 * @file interval_cover.cc
 * @author Bashar Al-Saify
 * @brief Implementation of the Interval Cover solver.
 */

#include "interval_cover.h"
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;


vector<int> solve_interval_cover(double target_start, double target_end, vector<Interval> candidates) {
    // If we only need to cover a single point [target_start, target_start]
    if (target_start == target_end) {
        for (const auto& candidate : candidates) {
            if (candidate.start <= target_start && candidate.end >= target_start) {
                return {candidate.index};
            }
        }
        return {}; 
    }

    sort(candidates.begin(), candidates.end(), [](const Interval& a, const Interval& b) {
        return a.start < b.start;
    });

    vector<int> result;
    double current_reach = target_start;
    int num_intervals = candidates.size();
    int idx = 0;

    while (current_reach < target_end) {
        double max_end = current_reach;
        int max_original_index = -1;
        
        // Greedily find the interval starting before current_reach that extends the furthest
        while (idx < num_intervals && candidates[idx].start <= current_reach) {
            // Only update if it actually extends our reach
            if (candidates[idx].end > max_end) {
                max_end = candidates[idx].end;
                max_original_index = candidates[idx].index;
            }
            idx++;
        }

        // Check if we failed to find any interval that extends coverage
        if (max_original_index == -1) {
            return {};
        }

        result.push_back(max_original_index);
        current_reach = max_end;
    }

    return result;
}
