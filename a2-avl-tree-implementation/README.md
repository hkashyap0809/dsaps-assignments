# AVL Tree

#### AIM: <br/>
To have end to end knowledge of the balanced binary search tree and how it can
be used to solve a wide range of problems efficiently. 
### TASK: 
Implement AVL Tree with Following Operations .

#### IMPORTANT POINTS:
Implement it with a class or struct. It should be generic, along with the primitive data structures(integer, float, string, etc) your code should also be able to handle class objects.<br/>

Duplicates are allowed. (We know that AVL trees don't have duplicates but in this task you have to handle it.)
 
For strings, you can simply compare them but for Class data type, you have to pass the comparator object so that you can compare two objects.

For strings and custom Class objects, you don’t need to implement the Closest Element operation.

Instruction for Class data type: Name your custom comparator function as “cmprtr”. Strictly follow this convention as we’ll also be evaluating the program on our custom class and its custom comparator function (which will be named "cmprtr”)

### Tasks:
Assuming the data type to be element to be T e, where T is type of element e

#### 1. insert(e):
Inserts e into the tree.

#### 2. delete(e):
Deletes all the occurrences of the element e, if it is present in the tree.

#### 3. bool search(e):
Returns true if e is present in the tree, otherwise returns false.

#### 4. int count_occurence(e):
Returns the count of occurrences of the element e.<br/>
Eg. If the tree has the following elements: 1, 1, 2, 2, 2, 3<br/>
count_occurence(2) will return 3.<br/>
count_occurence(734) will return 0.

#### 5. T lower_bound(e):
Return the first element that is greater than or equal to e. If no such element exists, return default value for type T.<br/>

Eg. If the tree has the following elements: 1, 1, 2, 2, 2, 3
lower_bound(2) will return element corresponding to 2 i.e. 3rd element from the left.<br/>

If the tree has the following elements 1, 1, 2, 5, 6, 6, 7
lower_bound(3) will return element corresponding to 5 i.e. 4th element from the left.

#### 6. T upper_bound(e):
Return the first element that is greater than e. If no such element exists, return default value for type T.<br/>

Eg. If the tree has the following elements: 1, 1, 2, 2, 2, 3<br/>
upper_bound(2) will return element corresponding to 3 i.e. last element from the right.<br/>

If the tree has the following elements: 1, 1, 2, 5, 6, 6, 7
upper_bound(7) will return 0 i.e. the default value for the type of element e (integer in this case)

#### 7. T closest_element(e):
Returns the element closest to e.
If no such element exists, return default value for type T.<br/>
Eg. If the tree has the following elements: 1, 1, 2, 2, 2, 5.<br/>
closest_element(2) will return 2.<br/>
closest_element(3) will return 2.<br/>
closest_element(4) will return 5.<br/>
closest_element(-1472) will return 1.

#### 8. T Kth_largest(int k):
Returns the Kth largest element.
If no such element exists or k is invalid, return default value for type T.<br/>
Eg. If the tree has the following elements: 1, 1, 2, 2, 2, 3<br/>
Kth_largest(1) will return 3.<br/>
Kth_largest(2) will return 2.<br/>
Kth_largest(3) will return 2.<br/>
Kth_largest(4) will return 2.<br/>
Kth_largest(5) will return 1.<br/>
Kth_largest(9) will return 0 i.e. the default value for the type of element e (integer in this case)

#### 9. int count_range(T eLeft, T eRight):
Returns the count of the elements that lie in the range [eLeft, eRight] If eLeft > eRight or any other invalid case return 0<br/>
Eg. If the tree has the following elements: 1, 1, 2, 2, 2, 3, 4, 5, 6
count_range(1, 6) will return 9.<br/>
count_range(2, 3) will return 4.<br/>
count_range(2, 2) will return 3.<br/>
count_range(3, 10) will return 4.
