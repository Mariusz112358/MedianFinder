#include <iostream>
#include "imedian_computer.h"
#include "bst_median.h"
#include "split_median.h"

int main(int argc, char *argv[])
{    
    IMedianComputer *algs[] = { new BSTMedian(), new SplitMedian };
    int size = sizeof( algs ) / sizeof( IMedianComputer *);
    std::string text = "";
    while( text != "." ) {
        std::cin >> text;
        int val = 0;
        try {
            val = std::stoi( text );
            algs[0]->add( val );
            algs[1]->add( val );
            std::cout << "BST median: " << algs[0]->getMedian() << std::endl;
            std::cout << "Split median: " << algs[1]->getMedian() << std::endl;
        } catch ( std::exception &e ) {
            std::cout << "Non-numeric value provided! " << std::endl;
        }
    }

    for( int j = 0; j < size; ++j ) {
        delete algs[j];
    }
    return 0;
}
