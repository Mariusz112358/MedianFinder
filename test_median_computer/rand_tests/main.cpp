#include <iostream>
#include "imedian_computer.h"
#include "bst_median.h"
#include "split_median.h"
using namespace std;

#include <algorithm> //for test purposes
#include <vector>
#include <random>
#include <functional>
#include <chrono>
#include <thread>

#define SUPRESS_OUTPUT

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

void process( std::vector<int> &data ) {
    const int algNum = 2;
    const char *algNames[algNum] = { "BSTMedian", "SplitMedian" };
    IMedianComputer *medianAlgs[algNum] = { new BSTMedian, new SplitMedian };
    for( int i = 0; i < algNum; ++i ) {
        cout << algNames[i] << ": " << medianAlgs[i]->getMedian() << endl;
    }

    cout << "TEST SET: ";
    for( int i = 0; i < data.size(); ++i ) {
        cout << data[i] << ", ";
    }
    cout << endl;
    cout << endl;

    testVec.clear();
    cout << " |  STL  |" << "|  SPLIT  |" << "|  BST  |" << endl;
    double stl, bst, split;
    std::vector<double> time(3, 0.0);
    int errors = 0;
    for( int i = 0; i < data.size(); ++i ) {
#ifndef SUPRESS_OUTPUT
        cout << i + 1 << ": ";
#endif
        auto start = std::chrono::steady_clock::now();
        stl = getStlMedian( data[i] );
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                            (std::chrono::steady_clock::now() - start);
        time[0] += duration.count();

#ifndef SUPRESS_OUTPUT
        cout << "| " << stl << " |";
#endif

        medianAlgs[1]->add( data[i] );
        start = std::chrono::steady_clock::now();
        split = medianAlgs[1]->getMedian();
        duration = std::chrono::duration_cast<std::chrono::microseconds>
                            (std::chrono::steady_clock::now() - start);
        time[1] += duration.count();
#ifndef SUPRESS_OUTPUT
        cout << "| " << split << " |";
#endif

        medianAlgs[0]->add( data[i] );
        start = std::chrono::steady_clock::now();
        bst = medianAlgs[0]->getMedian();
        duration = std::chrono::duration_cast<std::chrono::microseconds>
                            (std::chrono::steady_clock::now() - start);
        time[2] += duration.count();
#ifndef SUPRESS_OUTPUT
        cout << "| " << bst << " |";
#endif
        if( !( almost_equal( bst, split, 4 ) && almost_equal( split, stl, 4 ) && almost_equal( stl, bst, 4 ) ) ) {
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
            ++errors;
        }
#ifndef SUPRESS_OUTPUT
        cout << endl;
#endif
    }
    cout << endl;

    for( int i = 0; i < time.size(); ++ i ) {
        std::cout << time[i] << " ,";
    }
    std::cout << endl;

    for( int i = 0; i < algNum; ++i ) {
        delete medianAlgs[i];
    }
    cout << "Errors num: " << errors << endl;
}

std::vector<int> generateData( int num = 1000 ) {
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist(-10, 10 );
    auto dice = std::bind( dist, gen );
    std::vector<int> outData;
    for( int i = 0; i < num; ++i ) {
        outData.push_back( dice() );
    }
    return outData;
}

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;    
    std::vector<int> testData = {1,100,0,0,1,2,3,2,8,9,1,3,5,3};
    //process( testData );
    auto randData = generateData();
    process( randData );
    return 0;
}
