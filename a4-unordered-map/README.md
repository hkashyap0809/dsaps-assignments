# Unordered Map

## Aim: 
To learn how Hashing works and the importance of the Hash Function.
## Functions to implement:

### insert(key, value) <br/>
insert the key-value pair. If the key already exists, update the value corresponding to the given key.
### erase(key)
erase if the key is present otherwise do nothing.
### find(key)
returns true if the key exists otherwise returns false. map[key] – returns the value mapped to the key. If the key does not exist, return the default value of the datatype as the mapped value to the key.

#### Note:
- Your unordered map should be generic i.e. it should be able to handle (int, float, char, double, string) data types.<br/>
- You have the liberty to choose between open addressing and chaining to handle hash collisions.<br/>

### Input Format
First Line will contain a single integer q denoting the number of queries. The next lines for each query follow the following pattern:<br/>
The first line will contain a single integer denoting the type of operation. [1 -> insert, 2 -> erase, 3 -> find, 4 -> map]<br/>
The second line will contain inputs based on the type of operation.<br/>
Type 1: 2 strings denoting the key, and value to be inserted respectively.<br/>
Type 2: 1 string denoting the key to be erased.<br/>
Type 3: 1 string denoting the key to be found.<br/>
Type 4: 1 string denoting the key on which operation must be applied.<br/>

### Output Format<br/>
Type 1: print nothing.<br/>
Type 2: print nothing.<br/>
Type 3: 1 if your output is true, 0 if your output is false.<br/>
Type 4: print the value associated with the key.<br/>