#include "split_median.h"
#include <assert.h>
#include <memory.h>

SplitMedian::SplitMedian()
{

}

SplitMedian::~SplitMedian()
{
    if( _data != nullptr ) {
        delete []_data;
        _data = nullptr;
    }
}

void SplitMedian::add(int val)
{
    if( _size == _allocatedSize ) {
        reallocMem();
    }
    assert( _size < _allocatedSize );
    _data[_size] = val;
    ++_size;
}

double SplitMedian::getMedian()
{
    if( _data == nullptr || _size == 0 ) {
        return int();
    }

    double median = 0;
    if( _size % 2 == 0 ) {
        int medianIdx1 = _size / 2 - 1;
        int medianIdx2 = ( _size + 2 ) / 2 - 1;
        median = ( *findStatistic( _data, _data + ( _size - 1 ), medianIdx1 ) +
                 *findStatistic( _data, _data + ( _size - 1 ), medianIdx2 ) ) / 2.0;
    } else{
        int medianIdx = ( ( _size + 1 ) / 2 ) - 1;
        median = *findStatistic( _data, _data + ( _size - 1 ), medianIdx );
    }
    return median;
}

int* SplitMedian::findStatistic(int *beg, int *end, int medianIdx)
{
    if( beg == end ) {
        return beg;
    }
    assert(medianIdx >= 0);
    int *splitEl = partitionAndFindElement( beg, end );
    int splitElPos = distance( beg,splitEl );
    if( splitElPos == medianIdx ) {
        return splitEl;
    } else {
        return medianIdx < splitElPos ? findStatistic( beg, splitEl - 1, medianIdx ) :
                                  findStatistic( splitEl + 1, end, medianIdx - splitElPos - 1 );
    }
}

int* SplitMedian::partitionAndFindElement(int *beg, int *end)
{
    int mid = distance( end, beg ) / 2;
    swap( beg+mid, end );
    return partition(beg, end);
}

int* SplitMedian::partition(int *beg, int *end)
{
    int size = distance( beg, end );
    int partitionEl = *end;
    int lastSmallerIdx = 0;
    for( int i=0 ; i < size; ++i ) {
        if(beg[i] <= partitionEl) {
            swap( beg + i, beg + lastSmallerIdx );
            ++lastSmallerIdx;
        }
    }
    swap( beg + lastSmallerIdx, end );
    return beg + lastSmallerIdx;
}

int SplitMedian::distance(int *addr1, int *addr2)
{
    return abs( addr2 - addr1 );
}

void SplitMedian::reallocMem()
{
    assert( _size == _allocatedSize );

    int newAllocatedSize = _size + _allocateStep;
    int *newData = new int[newAllocatedSize];
    if( _data != nullptr ) {
        memcpy( newData, _data, _size * sizeof(int) );
        delete []_data;
    }

    _data = newData;
    _allocatedSize = newAllocatedSize;
}

int SplitMedian::abs(int val)
{
    return ( val >= 0 ? val : -val );
}

void SplitMedian::swap(int *val1, int *val2)
{
    int tmp = *val1;
    *val1 = *val2;
    *val2 = tmp;
}
