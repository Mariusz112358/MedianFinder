#ifndef BSTMEDIAN_H
#define BSTMEDIAN_H
#include "imedian_computer.h"
#include <iostream>

class BSTMedian : public IMedianComputer
{
public:
    BSTMedian();
    ~BSTMedian();

    void add(int val) final override;
    double getMedian() final override;
private:
    struct Node {
        Node( int v, Node *par ) :
            value(v), size(1), subTreeSize(0),
            p(par), l(nullptr), r(nullptr)
        {}
        ~Node();
        int value = 0;
        int size = 0;
        int subTreeSize = 0;
        Node *p = nullptr;
        Node *l = nullptr;
        Node *r = nullptr;
    } *_root = nullptr;

    Node *insertInternal(Node *curr, int val);
        int getSizeIncluding( Node *curr );
    double findMedian();
};

#endif // BSTMEDIAN_H
