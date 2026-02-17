# Problem B - Knapsack B

Given a knapsack with a maximum weight capacity and a set of items (each having a specific weight and value), the goal is to determine the subset of items to include in the knapsack such that the total weight is less than or equal to the capacity and the total value is maximized.

## Input
The input consists of several test cases. Each test case begins with two integers `C` and `n`, where `1 <= C <= 2000` is the capacity of the knapsack and `1 <= n <= 2000` is the number of items available.
After this follow `n` lines, each containing two integers `v` and `w`, indicating the value and weight of an item.

## Output
For each test case, output one line containing the number of items in an optimal solution, followed by a line containing the indices of these items (0-based). The indices can be given in any order.

### Sample input 1
```
5 3
1 5
10 5
100 5
6 4
5 4
4 3
3 2
2 1
```

### Sample output 1
```
1
2
3
3 2 1
```