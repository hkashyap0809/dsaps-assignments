# LRU and LFU cache
## A. LRU Cache
Implement a LRU cache (Least Recently Used) Cache. It should support following functions:
<br/>

- constructor(capacity): Creates the cache with given capacity.<br/>
- get(key): Return the value associated with the key, if not present return -1.<br/>
- set(key, value): Insert a new key value pair in the cache or update if
already present. If the capacity of the cache is exceeded, then replace with the Least recently used element from the cache.<br/>

## B. LFU Cache
Implement a LFU cache (Least Frequently Used) Cache. It should support following functions:<br/>

- constructor(capacity): Creates the cache with given capacity.<br/>
- get(key): Return the value associated with the key, if not present return -1.<br/>
- set(key, value): Insert a new key value pair in the cache or update if
already present. If the capacity of the cache is exceeded, then replace it with the Least Frequently Used element. If there is tie among the Least frequent elements, choose the Least Recently Used element.

<br/>
NOTE:
You are not allowed to use any STL data structures except the map/set (any of the ordered or unordered can be used).<br/>

### Constraints:
1 <= Key, Value <= 10^9
1 <= Capacity <= 10^3
1 <= No. of Queries <= 10^6
### Operations:
1. int get(int key)
2. void set(int key, int val)

### Input Format:
- First line of input contains two space separated integers cap and q respectively. Where cap represents the capacity of cache to be initialized and q denotes the number of queries.
  
- Following q lines contain two (in case of get() method, or three in case of set() method) space separated integers. Where the first integer represents the type of operation. 1 for get() and 2 for set(). Second integer will be the key. Third integer (in case of set method) will be the val to be associated with the key.<br/>
#### Note:
- Cache will be initialized only once.<br/>
- In set(key, v2) method: If the key is already present with value v1, associate new value (i.e. v2) with the key(overwrite v1 by v2) and update the least recently/frequently used cache accordingly. (check sample test case)<br/>

### Output format:
- For every type 1 operation(i.e. get() method) return and print the val associated with the key in a new line. If the key is not present in the cache return and print -1.
- You don't have to print anything in case of type 2 operation(i.e. set() method).

Sample Test Case: (for LRU cache, format will be same for LFU cache)
<br/>
- Input:<br/>
2 10<br/>
2 1 11<br/> 
2 5 55 <br/>
1 1<br/>
1 3<br/> 
1 5<br/>
2 4 44<br/>
1 1<br/>
2 5 50<br/>
1 4<br/>
1 5<br/>
- Output<br/> 
11<br/>
-1<br/>
55<br/>
-1<br/>
44<br/>
50<br/>