#include <iostream>
#include "imedian_computer.h"
#include "tree_median/bst_median.h"
#include "tree_median/rbt_median.h"
#include "split_median.h"
#include "heap_median/heap_median.h"

//For testing purposes
#include <algorithm>
#include <vector>
#include <random>
#include <functional>
#include <chrono>
#include <thread>

std::vector<int> testVec;
double getStlMedian( int val ) {
    testVec.push_back( val );
    double median = 0.0;
    if( testVec.size() % 2 == 0 ) {
        std::nth_element( testVec.begin(), testVec.begin() + testVec.size() / 2, testVec.end());
        median += static_cast<double>( testVec[testVec.size() / 2] );
        std::nth_element( testVec.begin(), testVec.begin() + ( testVec.size() / 2 ) -1, testVec.end());
        median += static_cast<double>( testVec[testVec.size() / 2 - 1] );
        median /= 2.0;
    } else {
        std::nth_element( testVec.begin(), testVec.begin() + ( testVec.size() / 2 ), testVec.end());
        median = static_cast<double>( testVec[testVec.size() / 2] );
    }
    return median;
}

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x-y) < std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp
            // unless the result is subnormal
            || std::abs(x-y) < std::numeric_limits<T>::min();
}

void process( std::vector<int> &data, bool supressOut = false ) {
    const int myAlgNum = 4;
    IMedianComputer *medianAlgs[myAlgNum] = { new SplitMedian(), new BSTMedian(), new HeapMedian(), new RBTMedian() };
    testVec.clear();

    if( !supressOut ) {
        std::cout << "TEST SET: ";
        for( int i = 0; i < data.size(); ++i ) {
            std::cout << data[i] << ", ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    const int allAlgNum = myAlgNum + 1;
    const char *algNames[allAlgNum] = { "STL", "SPLIT", "BST", "HEAP", "RBT" };

    if( !supressOut ) {
        for( int i = 0; i < allAlgNum; ++i ) {
            std::cout << " | " << algNames[i];
        }
        std::cout << std::endl;
    }

    std::vector<double> time( allAlgNum, 0.0 );
    std::vector<double> results( allAlgNum, 0.0 );
    int errors = 0;
    for( int i = 0; i < data.size(); ++i ) {
        if( !supressOut ) {
            std::cout << i + 1 << ": ";
        }

        auto start = std::chrono::steady_clock::now();
        results[0] = getStlMedian( data[i] );
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                (std::chrono::steady_clock::now() - start);
        time[0] += duration.count();

        if( !supressOut ) {
            std::cout << "| " << results[0] << " |";
        }

        for( int j = 0; j < myAlgNum; ++j ) {
            medianAlgs[j]->add( data[i] );
            start = std::chrono::steady_clock::now();
            results[j+1] = medianAlgs[j]->getMedian();
            duration = std::chrono::duration_cast<std::chrono::microseconds>
                    (std::chrono::steady_clock::now() - start);
            time[j + 1] += duration.count();
            if( !supressOut ) {
                std::cout << "| " << results[j+1] << " |";
            }
        }

        for( int j = 0; j < results.size(); j++ ) {
            for( int k = j; k < results.size(); k++ ) {
                if( j == k ) {
                    continue;
                }

                if(!(almost_equal( results[j], results[k], 4 ))) {
                    ++errors;
                    std::cout << "Error on element: " << i << " with algorithms: "
                              << algNames[j] << " " << results[j] << " and " << algNames[k] << " " << results[k] << std::endl;
                }
            }
        }

        if( !supressOut ) {
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
    for( int i = 0; i < allAlgNum; ++ i ) {
        std::cout << "Working time for processing data one by one is: " << algNames[i] << " "
                  << time[i] << " microseconds." << std::endl;
    }
    std::cout << std::endl;

    for( int i = 0; i < myAlgNum; ++i ) {
        delete medianAlgs[i];
    }

    std::cout << "Errors num: " << errors << std::endl;
}

const int defaultlB = -10;
const int defaultuB = 10;
const int defaultNum = 100;
std::vector<int> generateData( int num = defaultNum, int lowerBound = defaultlB, int upperBound = defaultuB ) {
    if( lowerBound >= upperBound || num < 1 ) {
        std::cout << "Wrong data generation parameters! Setting default: " << std::endl;
        std::cout << "Elements num: " << num << ". Should be bigger than 0. Setting: " << defaultNum << std::endl;
        std::cout << "Lower bound: " << lowerBound << ". Should be lower than upper bound. Setting: " << defaultlB << std::endl;
        std::cout << "Upper bound: " << upperBound << ". Should be bigger than lower bound. Setting: " << defaultuB << std::endl;
        num = defaultNum;
        lowerBound = defaultlB;
        upperBound = defaultuB;
    }

    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist( lowerBound, upperBound );
    auto dice = std::bind( dist, gen );
    std::vector<int> outData;
    for( int i = 0; i < num; ++i ) {
        outData.push_back( dice() );
    }
    return outData;
}

int main(int argc, char *argv[])
{
    std::cout << "Running median algorithm testing by uniform random generator! To exit type: e" << std::endl;
    std::cout << "Set generator params: " << std::endl;
    const int paramNum = 3;
    int params[paramNum] = {0,0,0};
    const char *p[paramNum] = { "Number of generated elements (default 100): ",
                                "Elements lower bound (default -10): ",
                                "Elements upper bound (default 10): "
                              };
    std::string text = "";
    int reading = 0;
    while( text != "e" ) {
        if( reading < 3 ) {
            std::cout << p[reading];
            std::cin >> text;
            if( text != "e" ) {
                try {
                    params[reading] = std::stoi( text );
                    ++reading;
                } catch ( std::exception &e ) {
                    std::cout << "Non-numeric value provided! Try again. To exit type: e" << std::endl;
                    reading = 0;
                }
            }
        } else { //Start processing
            auto randData = generateData( params[0], params[1], params[2] );
            process( randData, true );
            reading = 0;
            std::cout << "FINISHED!" << std::endl;
        }
    }
    std::cout << "Program finished!" << std::endl;
    return 0;
}
