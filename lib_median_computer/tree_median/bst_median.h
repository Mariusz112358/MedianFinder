#ifndef BSTMEDIAN_H
#define BSTMEDIAN_H
#include "../imedian_computer.h"
#include <iostream>

class BSTMedian : public IMedianComputer
{
public:
    BSTMedian();
    virtual ~BSTMedian();

    void add(int val) override;
    double getMedian() override;

protected:
    struct Node {
        Node( int v, Node *par ) :
            value(v), size(1), subTreeSize(0),
            p(par), l(nullptr), r(nullptr)
        {}
        virtual ~Node();
        int value = 0;
        int size = 0;
        int subTreeSize = 0;
        Node *p = nullptr;
        Node *l = nullptr;
        Node *r = nullptr;
    };
    Node *_root = nullptr;

    int getSizeIncluding( Node *curr );
    double findMedian();
    Node *insertInternal(Node *curr, Node *newNode, Node **insertedNode );
private:
};

#endif // BSTMEDIAN_H
