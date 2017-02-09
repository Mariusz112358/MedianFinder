#include <iostream>
#include <fstream>
#include <string>
#include "imedian_computer.h"
#include "tree_median/bst_median.h"
#include "tree_median/rbt_median.h"
#include "split_median.h"
#include "heap_median/heap_median.h"

int main(int argc, char *argv[])
{    
    IMedianComputer *algs[] = { new BSTMedian(), new SplitMedian(), new HeapMedian(), new RBTMedian() };
    const char *algNames[] = { "BST", "Split", "Heap", "RBT" };
    int size = sizeof( algs ) / sizeof( IMedianComputer *);
    if( argc == 1 ) {
        std::cout << "No arguments provided. Waiting for input... To exit pass: e" << std::endl;
        std::string text = "";
        while( text != "e" ) {
            std::cout << "Next number: ";
            std::cin >> text;
            int val = 0;
            try {
                val = std::stoi( text );
                for( int i = 0; i < size; ++i ) {
                    algs[i]->add( val );
                    std::cout << algNames[i] <<" " << algs[i]->getMedian() << ", ";
                }
                std::cout << std::endl;
            } catch ( std::exception &e ) {
                std::cout << "Non-numeric value provided! " << std::endl;
            }
        }
    } else {
        std::string line;
        std::cout << "Reading from file. First file should be composed from input numbers separated by newline. " <<
                     "Second file if provided should contain expected results separated by newline." << std::endl;
        std::ifstream in( argv[1] );
        std::string secondFile = argc > 2 ? argv[2] : "";
        std::ifstream expected( secondFile );
        if( in.is_open() ) {
            while( std::getline( in, line ) ) {
                int val = 0;
                try {
                    if( expected.is_open() ) {
                        std::string secondFileLine;
                        if( std::getline( expected, secondFileLine ) ) {
                            try {
                                double res = std::stod( secondFileLine );
                                std::cout << "Expected: " << res << ", ";
                            } catch( std::exception &e ) {
                                std::cout << "Non-numeric value provided in SECOND file: " << secondFileLine << std::endl;
                            }
                        }
                    }
                    val = std::stoi( line );
                    for( int i = 0; i < size; ++i ) {
                        algs[i]->add( val );
                        std::cout << algNames[i] <<" " << algs[i]->getMedian() << ", ";
                    }
                    std::cout << std::endl;
                } catch( std::exception &e ) {
                    std::cout << "Non-numeric value provided in FIRST file: " << line << std::endl;
                }
            }

            in.close();
            if( expected.is_open() ) {
                expected.close();
            }
        } else {
            std::cout << "Unable to open first input file: " << argv[1] << std::endl;
        }
    }

    for( int j = 0; j < size; ++j ) {
        delete algs[j];
    }
    return 0;
}
