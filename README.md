# algorithms-cpp
Implementations of commonly used algorithms in C++

For instances of use please see main.cpp. 

Almost all of these are templated classes with easy to understand method names (most of the methods follow standard nomenclature). There is no library dependency of any sort; these sources have been tested on gcc 6.4. They will also work with MingW compilers.

Implementations of note are :

1. Red-Black Binary Search Tree
2. Interval Tree derived from Red-Black Binary Search Tree
3. Fenwick Tree (Binary Indexed Tree)
4. Segment Tree (Interface)
5. Trie

The included main.cpp runs unit tests. The expected output is shown below:
```
Testing stack<int>

Beginning unit test runs 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 11
6000, 65
11000, 118.667
16000, 172.667
21000, 227

Finished unit test runs 
Estimated time complexity is O(N*log(N))

Testing queue<int>

Beginning unit test runs 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 1351.67
2250, 5839
3500, 14236
4750, 26990.7
6000, 43113.3

Finished unit test runs 
Estimated time complexity is O(N^2)

Testing circular_queue<int>

Beginning unit test runs 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 15.6667
6000, 92
11000, 168
16000, 249.667
21000, 318

Finished unit test runs 
Estimated time complexity is O(N)

Testing heapsort<int>

Beginning unit test runs 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 139.333
11000, 2005.67
21000, 4083.67
31000, 6273.33
41000, 8921

Finished unit test runs 
Estimated time complexity is O(N*log(N))

Testing quicksort<int>

Beginning unit test runs 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 141
11000, 2001
21000, 4118.67
31000, 6313.33
41000, 8554

Finished unit test runs 
Estimated time complexity is O(N*log(N))


Process finished with exit code 0
```
