## Input
Standard input begins with an integer T=1, the number of test cases (this is not a typo, there is always exactly one test case).

Each test case consists of two polynomials. A polynomial is given by an integer 1 $\leq$ n $\leq$ 131071 indicating the degree of the polynomial, followed by a sequence of integers a_0, a_1, ..., a_n, where a_i is the coefficient of x^i in the polynomial. All coefficients will fit in a signed 32-bit integer.


NB! The input and output files for this problem are quite large, which means that you have to be a bit careful about I/O efficiency.


## Output
For each test case, output the product of the two polynomials, in the same format as in the input (including the degree). All coefficients in the result will fit in a signed 32-bit integer.


## Sample input 1
```
1
2
1 0 5
1
0 -2
```

## Sample output 1
```
3
0 -2 0 -10
```