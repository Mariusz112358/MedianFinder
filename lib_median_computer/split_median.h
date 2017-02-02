#ifndef SPLITMEDIAN_H
#define SPLITMEDIAN_H
#include "imedian_computer.h"

//TO_DO difference between STL and wiki
//simultanous finding of two near median values
class SplitMedian : public IMedianComputer {
public:
    SplitMedian();
    ~SplitMedian();

    void add(int val) final;
    double getMedian() final;

private:
    const int _allocateStep = 64;
    int *_data = nullptr;
    int _size = 0;
    int _allocatedSize = 0;

    int* findStatistic(int *beg, int *end, int medianIdx);
        int *partitionAndFindElement( int *beg, int *end );
            int *partition( int *beg, int *end );
    inline int distance(int *addr1, int *addr2 );
    inline int abs( int val );
    inline void swap( int *val1, int *val2 );
    void reallocMem();
};

#endif // SPLITMEDIAN_H
