# Sparse Matrix Operations

A matrix is generally represented using a 2D array. A sparse matrix is a matrix which has the majority of its elements set as 0. So using a conventional matrix representation scheme wastes a lot of memory. You are required to come up with a representation of how you will store a sparse matrix in memory using an array and linked list. And after that you are required to implement an algorithm to perform addition, multiplication and transpose of the matrices. For addition and multiplication operations you will be provided two sparse matrices in conventional format (conventional format is the usual representation of a 2D matrix in row x column) and the return value should be the sum and product of the two matrices itself, respectively. Incase of transpose operation you will be provided only one sparse matrix in conventional format and you have to return its transpose.

## Task:

### 1. Add:
- Takes two matrices as input (M1 and M2).
- Performs matrix addition on these two matrices.
- Test cases will be designed such that size of M1 = size of M2, no need to
handle the cases of unequal size
- Print the result of matrix addition.
### 2. Transpose:
- Takes one matrix as input (M1).
- Performs matrix transpose.
- Print the result of matrix transpose
### 3. Multiply:
- Takes two matrices as input (M1 and M2).
- Performs matrix multiplication on these two matrices. (calculate M1 x M2)
- Test cases will be designed such that matrix M1 and M2 are multiplication
compatible.
- Print the result of matrix multiplication.

#### Input Format:
- First line contains type of data structure. <br/>
1 - Array<br />
2 - Linked List<br/>

- Second line of input contains type of operation<br/>
1 - Addition<br/>
2 - Transpose<br/>
3 - Multiplication<br/>

- Third line of input contains two space separated integers N, M number of rows and columns of the first matrix respectively(note that for transpose there will be only one input matrix)

- Following N lines will contain M space separated elements of the matrix.

- Next line will contain two space separated integers N2, M2 number of rows and columns of the second matrix respectively. (only in the case of
addition and multiplication)
- Following N2 lines will contain M2 space separated elements of matrix

#### Output Format:
- Print the Output matrix in conventional format (N rows, space separated M values in each row)
#### Constraints:
1 <= N, M <= 1000<br/>
Number of non-zero cells <= min(N*M, 10^5)

##### Note:

You are required to implement all the three operations using both the matrix
representation i.e. using arrays and as well as linked lists.

Make your code generic. The final code will be tested on all primitive data types:
int, double, float, etc(excluding string). So make sure you handle these cases as
well.