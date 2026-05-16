/**
 * @file interval_cover.h
 * @author Bashar Al-Saify
 * @brief  Solves the Interval Cover problem using a greedy approach.
 * 
 * Given a target interval [A, B] and a set of candidate intervals,
 * find the minimum number of intervals required to cover [A, B].
 */

#ifndef INTERVAL_COVER_H
#define INTERVAL_COVER_H

#include <vector>
#include <iostream>

struct Interval {
    double start;   
    double end;     
    int index;      
};

/**
 * @brief Finds the minimum set of intervals to cover the target range [target_start, target_end].
 * 
 * This function implements a greedy algorithm to solve the interval cover problem.
 * It sorts the candidate intervals by their start points and iteratively selects
 * the interval that extends the covered range the furthest.
 * 
 * @param target_start The start of the target interval to cover.
 * @param target_end The end of the target interval to cover.
 * @param candidates A vector of candidate intervals. Passing by value or making a copy inside is necessary to sort without modifying caller's data.
 *                  Here we take by value to allow internal sorting.
 * 
 * @return vector<int> A list of indices of the chosen intervals.
 *         Returns an empty vector if no cover is possible.
 * 
 * @complexity
 *  - Time: O(N log N) due to sorting, where N is the number of intervals.
 *          The linear scan after sorting takes O(N).
 *  - Space: O(N) to store the intervals and the result.
 */
std::vector<int> solve_interval_cover(double target_start, double target_end, std::vector<Interval> candidates);

#endif 
