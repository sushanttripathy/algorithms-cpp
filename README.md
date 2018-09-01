# algorithms-cpp
Implementations of commonly used algorithms and data structures in C++

For instances of use please see unit-tests referenced in main.cpp. 

Almost all of these are templated classes with easy to understand method names (most of the methods follow standard and/or self-evident of usage nomenclature). There is no library dependency of any sort; these sources have been tested on gcc 6.4. They will also work with MingW compilers.

Implementations of note are :

1. Red-Black Binary Search Tree
2. Interval Tree derived from Red-Black Binary Search Tree
3. Fenwick Tree (Binary Indexed Tree)
4. Segment Tree (Interface)
5. Trie

The included main.cpp runs unit tests. The expected output is shown below:
```
Testing stack<int>

Beginning unit test runs with time complexity analyses 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 0.0123333
6000, 0.067
11000, 0.122667
16000, 0.178333
21000, 0.234667

Finished unit test runs, all tests passed in 168.192 ms
Estimated time complexity is O(N)

Testing queue<int>

Beginning unit test runs with time complexity analyses 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 1.183
2250, 5.82033
3500, 14.7493
4750, 24.8947
6000, 39.95

Finished unit test runs, all tests passed in 4624.65 ms
Estimated time complexity is O(N^2)

Testing circular_queue<int>

Beginning unit test runs with time complexity analyses 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 0.0173333
6000, 0.092
11000, 0.16
16000, 0.237667
21000, 0.302667

Finished unit test runs, all tests passed in 55.859 ms
Estimated time complexity is O(N)

Testing heapsort<int>

Beginning unit test runs with time complexity analyses 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 0.146
11000, 1.927
21000, 3.93367
31000, 6.02
41000, 8.27733

Finished unit test runs, all tests passed in 1556.29 ms
Estimated time complexity is O(N*log(N))

Testing quicksort<int>

Beginning unit test runs with time complexity analyses 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 0.145
11000, 1.917
21000, 3.928
31000, 5.99467
41000, 8.11

Finished unit test runs, all tests passed in 1550.87 ms
Estimated time complexity is O(N*log(N))

Testing binary_search_tree<int>

Running BST insertion tests with complexity analyses
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

50000, 0.00316667
55000, 0.00333333
60000, 0.00366667
65000, 0.00383333
70000, 0.0035

Finished unit test runs, all tests passed in 1.208 ms
Estimated time complexity is O(log(N))


Running BST removal tests with complexity analyses
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

50000, 0.721667
55000, 0.448833
60000, 0.331333
65000, 0.525333
70000, 0.882167

Finished unit test runs, all tests passed in 223.615 ms
Estimated time complexity is O(N^3)


Running BST search tests with complexity analyses
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

50000, 0.00283333
55000, 0.00316667
60000, 0.00283333
65000, 0.003
70000, 0.00333333

Finished unit test runs, all tests passed in 0.979 ms
Estimated time complexity is O(log(N))

Testing red-black binary_search_tree<int>

Running Red-Black BST insertion tests with complexity analyses
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

50000, 0.0035
55000, 0.00366667
60000, 0.004
65000, 0.0035
70000, 0.0035

Finished unit test runs, all tests passed in 1.179 ms
Estimated time complexity is O(log(N))


Running Red-Black BST removal tests with complexity analyses
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

50000, 0.0593333
55000, 0.0505
60000, 0.259833
65000, 0.157167
70000, 0.151167

Finished unit test runs, all tests passed in 44.285 ms
Estimated time complexity is O(N^3)


Running Red-Black BST search tests with complexity analyses
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

50000, 0.00266667
55000, 0.00233333
60000, 0.0025
65000, 0.00283333
70000, 0.00266667

Finished unit test runs, all tests passed in 0.824 ms
Estimated time complexity is O(N)

Testing get_kth_element_1d<int>

Beginning unit test runs with time complexity analyses 
[======================================================================] 100 %
Input lengths (arbitrary units) and run times (ms) : 

1000, 0.107333
11000, 1.13867
21000, 2.11367
31000, 3.16567
41000, 4.167

Finished unit test runs, all tests passed in 763.593 ms
Estimated time complexity is O(N)
```
