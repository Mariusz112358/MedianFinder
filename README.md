# MedianFinder
Project contains four implementations of median finding from integer data stream (elements are coming one by one).
First one is based on quicksort partition of data in array. Inserting single element is O(1), finding median O(n).
Second one is based on binary search trees. Inserting O(log n), finding median O(log n), but pessimistic for both is O(n) as tree may be not balanced.
Third is based on two heaps: min and max. Inserting O(log n), finding median O(log n). The fastest solution in tests. 
Fourth is using red-black trees for self balancing of tree. Inserting O(log n), finding median O(log n).

* Median of odd number of sorted elements is computed as: x_n[( n + 1 ) / 2] 
* Median of even number of sorted elements is computed as: ( x_n[n/2] + x_n[(n+2)/2] ) / 2

#TESTING
### rand_tests 
Tests generates artificial data from uniform distribution and forwards it to five algorithms: split, bst, heaps, rbt and implementation based on stl nth_element. All three results are printed and any differences between those three are signaled on output.

### file_tests 
Tests can be defined by user based on input from console or file provided as program input. First parameter should be input file with each data separeted with newline, second file should provide expected results separated with newline. If file is not provided console input is read.

#Sample usage as library for BST median finder
```
#include "tree_median/bst_median.h"
#include <iostream>
...
IMedianComputer *p = new BSTMedian();
std::vector<int> data = { 6, 5, 4, 3, 8, 2, 4 };
for( const auto &d : data ) {
	p->add(d);
	std::cout << p->getMedian() << ", ";
}
std::cout << std::endl;
delete p;
```

