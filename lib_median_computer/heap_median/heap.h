#ifndef HEAP_H
#define HEAP_H

class Heap {
public:
    enum class Type {
        Min,
        Max
    };

    Heap( Type type );
    ~Heap();

    void push(int val);
    int top();
    int extractTop();
    int size();

private:
    const int _allocateStep = 128;
    int *_data = nullptr;
    int _size = 0;
    int _allocatedSize = 0;
    Type _type;
    inline bool comp(int idx1, int idx2 );

    void swap( int idx1, int idx2 );
    bool boundariesCheck( int nodeIdx );
    int p( int nodeIdx );
    int l( int nodeIdx );
    int r( int nodeIdx );
    void heapify( int nodeIdx );
    void heapInsert( int val );

    void reallocMem();
};

#endif // HEAP_H
