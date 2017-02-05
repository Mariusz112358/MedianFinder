#include "heap_median.h"

HeapMedian::HeapMedian() :
    _leftMaxHeap( Heap::Type::Max ),
    _rightMinHeap( Heap::Type::Min )
{
}

HeapMedian::~HeapMedian() {
}

void HeapMedian::add(int val) {
    val < _cmpEl ? _leftMaxHeap.push( val ) : _rightMinHeap.push( val );
    upMedian();
}

double HeapMedian::getMedian() {
    return _median;
}

void HeapMedian::upMedian() {
    int size = _leftMaxHeap.size() + _rightMinHeap.size();
    if( size % 2 ) {
        _cmpEl = _leftMaxHeap.size() > _rightMinHeap.size() ?
                    _leftMaxHeap.top() :
                    _rightMinHeap.top();
        _median = static_cast<double>( _cmpEl );
    } else {
        if( _leftMaxHeap.size() > _rightMinHeap.size() ) {
            _rightMinHeap.push( _leftMaxHeap.extractTop() );
        } else if( _rightMinHeap.size() > _leftMaxHeap.size() ) {
            _leftMaxHeap.push( _rightMinHeap.extractTop() );
        }
        _cmpEl = _rightMinHeap.top();
        _median = static_cast<double>( _leftMaxHeap.top() + _rightMinHeap.top() ) / 2.0;
    }
}
