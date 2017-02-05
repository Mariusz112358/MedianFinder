#ifndef HEAPMEDIAN_H
#define HEAPMEDIAN_H
#include "../imedian_computer.h"
#include "heap.h"

class HeapMedian : public IMedianComputer {
public:
    HeapMedian();
    ~HeapMedian();

    virtual void add(int val) final override;
    virtual double getMedian()  final override;

private:
    Heap _leftMaxHeap;
    Heap _rightMinHeap;
    int _cmpEl = 0;
    double _median = 0.0;

    void upMedian();
};

#endif // HEAPMEDIAN_H
