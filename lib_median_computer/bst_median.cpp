#include "bst_median.h"
#include <assert.h>

BSTMedian::BSTMedian()
{

}

BSTMedian::~BSTMedian()
{
    if( _root != nullptr ) {
        delete _root;
        _root = nullptr;
    }
}

void BSTMedian::add(int val)
{
    if( _root == nullptr ) {
        _root = new Node(val, nullptr);
    } else {
        Node *curr = _root;
        insertInternal( curr, val );        
    }
}

double BSTMedian::getMedian()
{
    if( _root != nullptr ) {
        return findMedian();
    } else {
        return 0;
    }
}

BSTMedian::Node* BSTMedian::insertInternal(BSTMedian::Node *curr, int val)
{
    if( curr == nullptr ) {
        return new Node( val, curr );
    }

    if( curr->value == val ) {
        ++curr->size;
    } else {
        ++curr->subTreeSize;
        Node **children[] = { &curr->l, &curr->r };
        Node **child = val < curr->value ? children[0] : children[1];
        (*child) = insertInternal( *child,val );
        (*child)->p = curr;
    }

    return curr;
}

int BSTMedian::getSizeIncluding(BSTMedian::Node *curr)
{
    return curr != nullptr ? curr->subTreeSize + curr->size : 0;
}

double BSTMedian::findMedian()
{
    int treeSize = getSizeIncluding( _root );
    int medianIdx[2] = {0,0};
    if( treeSize % 2 == 0 ) {
        medianIdx[0] = treeSize / 2;
        medianIdx[1] = ( treeSize + 2 ) / 2;
    } else{
        medianIdx[0] = ( ( treeSize + 1 ) / 2 );
    }

    double div = 0.0;
    double median = 0.0;
    for( int i = 0; i < 2; ++i ) {
        if( medianIdx[i] ) {
            Node *curr = _root;
            while( curr != nullptr ) {
                int leftSubSize = getSizeIncluding( curr->l );
                if( medianIdx[i] <= leftSubSize ) {
                    curr = curr->l;
                } else if( medianIdx[i] > ( leftSubSize + curr->size ) ) {
                    medianIdx[i] -= ( leftSubSize + curr->size );
                    curr = curr->r;
                } else {
                    median += static_cast<double>( curr->value );
                    break;
                }
            }
            div += 1.0;
        }
    }
    return div != 0.0 ? median / div : double();
}

BSTMedian::Node::~Node() {
    if( l != nullptr ) {
        delete l;
        l = nullptr;
    }

    if( r != nullptr ) {
        delete r;
        r = nullptr;
    }
}
