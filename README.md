# MedianFinder
Project contains two implementations of median finding from data stream (elements are coming one by one).
First one is based on quicksort partition of data in array.
Second one is based on binary search trees.

* Median of odd number of sorted elements is computed as: x_n[( n + 1 ) / 2] 
* Median of even number of sorted elements is computed as: ( x_n[n/2] + x_n[(n+2)/2] ) / 2

#TESTING
### rand_tests 
Tests generates artificial data from uniform distribution and forwards it to three algorithms: split, bst and implementation based on stl nth_element. All three results are printed and any differences between those three are signaled on output.

### file_tests 
Tests can be defined by user based on input from console or file provided as program input. First parameter should be input file with each data separeted with newline, second file should provide expected results separated with newline.

#Sample usage as library for BST median finder
```
IMedianComputer *p = new BSTMedian();
std::vector<int> data = { 6, 5, 4, 3, 8, 2, 4 };
for( const auto &d : data ) {
	p->add(d);
	std::cout << p->getMedian() << ", ";
}
std::cout << std::endl;
delete p;
```

