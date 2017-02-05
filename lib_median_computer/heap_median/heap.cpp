#include "heap.h"
#include <assert.h>
#include <memory.h>
#include <iostream>

Heap::Heap(Type type ) :
    _type(type)
{
    _data = new int[_allocateStep];
    _allocatedSize = _allocateStep;
}

Heap::~Heap()
{
    if( _data != nullptr ) {
        delete []_data;
        _data = nullptr;
    }
}

void Heap::push(int val) {
    ++_size;
    if( _size == _allocatedSize ) {
        reallocMem();
    }
    heapInsert( val );
}

int Heap::top() {
    return _data[1];
}

int Heap::extractTop() {
    int val = _data[1];
    swap( 1, _size );
    --_size;
    heapify( 1 );
    return val;
}

int Heap::size() {
    return _size;
}

bool Heap::comp( int idx1, int idx2 ) {
    return _type == Type::Max ? _data[idx2] >= _data[idx1] : _data[idx1] >= _data[idx2];
}

void Heap::swap(int idx1, int idx2) {
    int tmp = _data[idx1];
    _data[idx1] = _data[idx2];
    _data[idx2] = tmp;
}

bool Heap::boundariesCheck(int nodeIdx) {
    return nodeIdx > 0 && !(nodeIdx > _size);
}

int Heap::p(int nodeIdx) {
    if( boundariesCheck(nodeIdx) )
        return nodeIdx >> 1;
    std::cout << "Index in Heap::p() out of range! " << nodeIdx << " ,size: " << _size << std::endl;
    assert(0);
    return -1;
}

int Heap::l(int nodeIdx) {
    if( boundariesCheck(nodeIdx) )
        return nodeIdx << 1;
    std::cout << "Index in Heap::l() out of range! " << nodeIdx << " ,size: " << _size << std::endl;
    assert(0);
    return -1;
}

int Heap::r(int nodeIdx) {
    if( boundariesCheck(nodeIdx) )
        return ( nodeIdx << 1 ) + 1;
    std::cout << "Index in Heap::r() out of range! " << nodeIdx << " ,size: " << _size << std::endl;
    assert(0);
    return -1;
}

void Heap::heapify(int nodeIdx) {
    if( boundariesCheck( nodeIdx ) ) {
        int children[2] = { l(nodeIdx), r(nodeIdx) };
        int topIdx = nodeIdx;
        for( int i = 0; i < 2; ++i ) {
            if( boundariesCheck( children[i] ) ) {
                if( !comp( children[i], topIdx ) ) {
                    topIdx = children[i];
                }
            }
        }

        if( topIdx != nodeIdx ) {
            swap( nodeIdx, topIdx );
            heapify( topIdx );
        }
    } else {
        std::cout << "Index in Heap::heapify() out of range! " << nodeIdx << " ,size: " << _size << std::endl;
        assert(0);
    }
}

void Heap::heapInsert(int val) {
    int idx = _size;
    int parent = idx;
    _data[idx] = val;
    do {
        parent = p(idx);
        if( boundariesCheck(parent) ) {
            if( !comp( idx, parent ) ) {
                swap( idx, parent );
                idx = parent;
            }
        }
    } while( parent == idx );
}

void Heap::reallocMem() {
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
