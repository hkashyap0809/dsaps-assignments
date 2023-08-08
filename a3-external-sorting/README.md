# External Sorting 
## Aim:
External Sorting is a class of algorithms used to deal with massive amounts of data that do not fit in memory.The question aims at implementing one such type: K-Way merge sort algorithm to sort a very large array. This algorithm is a perfect example of the use of divide and conquer where with limited resources large problems are tackled by breaking the problem space into small computable subspaces and then operations are done on them.
## Task:
### Input format:
- Input.txt contains space separated integers.
- Program should take two command line arguments.
- First command line argument is the input file path.
- Second command line argument is the output file path.
- For example: You have a directory named data in your current
working directory inside which you have kept the input.txt file and you wish to create output.txt inside the data directory itself.
Then, run the program using the following command.
         ./a.out ./data/input.txt ./data/output.txt
- Input files can be arbitrarily large.
### Output Format:
- Print the following details in the terminal window:
- Number of integers in a temporary file.
- Number of temporary files created.
- Total time taken by the program upto 2 decimal places.
- Output file should contain integers in non-descending sorted order in a new line.
Given a file containing a large unsorted list of integers (Will not fit in your usual Laptop RAM) as input, generate an output file with non-descending sorted list of given integers.

### Evaluation Parameters:
- Correctness.
- Time and space complexity of the algorithm.
- Efficient use of data structures.
- Generation of unsorted file
- To generate the unsorted file, a python script is uploaded along with this pdf. It contains all the instructions required to run it.

#### Note: You are allowed to use vector and inbuilt sort for this problem