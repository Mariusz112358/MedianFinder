#ifndef BSTMEDIAN_H
#define BSTMEDIAN_H
#include "imedian_computer.h"
#include <iostream>

class BSTMedian : public IMedianComputer
{
public:
    BSTMedian();
    ~BSTMedian();

    void add(int val) final;
    double getMedian() final;
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
    //unused now
    void updateMedian();
        void swapParentChild( Node *parent, Node *child );
            void assignNodes( Node *parent, Node *lChild, Node *rChild );
                void setChildren( Node *parent, Node *lChild, Node *rChild, bool writeNull = true );
                void setParent( Node *lChild, Node *rChild, Node *parent );
};

#endif // BSTMEDIAN_H
