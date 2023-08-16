# Deque
## Problem Statement: Implementation of Deque

### What is deque?<br/>
Deque is the same as dynamic arrays with the ability to resize
itself automatically when an element is inserted or deleted, with
their storage being handled automatically by the container<br/>
- They support insertion and Deletion from both ends in amortised
constant time.<br/>
- Inserting and erasing in the middle is linear in time.<br/>

#### Expected Solution:
The C++ standard specifies that a legal (i.e., standard-conforming) implementation of deque must satisfy the following performance requirements: (consider the data type as T)

### 1. deque() <br/>
initialise a empty deque.Time complexity: O(1)

### 2. deque(n, x) <br/>
initialise a deque of length n with all values as x.Time complexity: O(n)

### 3. void push_back(x)
append data x at the end.Time complexity: O(1)

### 4. void pop_back()
erase data at the end. Time complexity: O(1)

### 5. void push_front(x) 
append data x at the beginning. Time complexity: O(1)

### 6. void pop_front()
erase an element from the beginning. Time complexity: O(1)

### 7. T front()
returns the first element(value) in the deque. Time complexity: O(1)

### 8. T back() 
returns the last element(value) in the deque. Time complexity: O(1)

### 9. T D[n] <br/>
returns the nth element of the deque. You need to overload the [ ] operator. Time complexity: O(1)

### 10. bool empty()<br/>
returns true if deque is empty else returns false. Time complexity: O(1)

### 11. int size() 
returns the current size of deque(i.e. the number of elements present in the deque). Time complexity: O(1)

### 12. void resize(x, d)
change the size dynamically to new size x. Time complexity: O(n)<br/>
- If the new size x is greater than the current size of the deque, then insert new elements with default value d at the end of the queue.
- If the new size x is smaller than the current size, then keep x elements from the beginning of the deque.

### 13. void clear()
remove all elements of deque. Time complexity: O(1)

#### Note: 
- Your deque should be generic type i.e. it should be datatype independent and can support primitive datatypes like integer, float, string, etc.<br/>
- Hint: Use template in C++ <br/>
- For 1. and 2. You can either define a constructor for the class or initialise the class object using void return type functions.<br/>
#### Evaluation parameters: 
Accuracy of operations and performance.