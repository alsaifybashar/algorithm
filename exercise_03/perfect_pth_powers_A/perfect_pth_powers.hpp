#ifndef PERFECT_PTH_POWERS_HPP
#define PERFECT_PTH_POWERS_HPP

class PerfectPthPowersSolver {
public:
    /**
     * @brief Finds the largest p such that x = b^p for some integer b.
     *
     * Uses prime factorization via trial division, then computes
     * the GCD of all prime exponents. For negative x, only odd
     * exponents are valid, so the result is the largest odd
     * divisor of that GCD.
     *
     * @param x The input integer. Must satisfy |x| >= 2.
     * @return The largest integer p >= 1.
     *
     * @note Time Complexity:  O(sqrt(|x|))
     */
    int solve(long long x);
};

#endif
