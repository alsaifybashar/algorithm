# Perfect Pth Powers

**Author:** Bashar Al-Saify

## Problem

Given an integer `x` (with `|x| >= 2`, within 32-bit int range), determine the largest integer `p` such that `x = b^p` for some integer `b`.

Input consists of one integer per line; the sequence is terminated by `0`.

## Algorithm

1. **Handle sign** — If `x` is negative, we work with `|x|` and restrict the answer to odd exponents only (since an even power can never be negative).
2. **Prime factorisation via trial division** — Divide `|x|` by each candidate factor `f` (2, then 3, 5, 7, … up to `√|x|`), counting the exponent of each prime factor.
3. **GCD of exponents** — The largest `p` for positive `x` equals the GCD of all prime-factor exponents. For example, `1073741824 = 2^30`, so `p = 30`.
4. **Odd restriction for negatives** — If `x < 0`, we take the largest odd divisor of that GCD (repeatedly divide by 2).

## Complexity

| Metric | Bound |
|--------|-------|
| **Time** | O(√\|x\|) per test case (trial division) |
| **Space** | O(log \|x\|) (number of distinct prime factors) |

## Usage

```bash
# Compile
g++ -O2 main.cpp perfect_pth_powers.cpp -o perfect_pth_powers

# Run with file input
./perfect_pth_powers < sample_intput.in

# Run interactively (enter integers, terminate with 0)
./perfect_pth_powers
```

### Assumptions

- Each input value `x` satisfies `|x| >= 2` and fits in a 32-bit signed integer.
- The input is terminated by a line containing `0`.

## File Structure

| File | Purpose |
|------|---------|
| `perfect_pth_powers.hpp` | Solver API — `PerfectPthPowersSolver::solve(long long x)` |
| `perfect_pth_powers.cpp` | Algorithm implementation (factorisation + GCD) |
| `main.cpp` | I/O driver (reads from stdin, prints results) |

## Sample

**Input:**
```
17
1073741824
25
0
```

**Output:**
```
1
30
2
```
