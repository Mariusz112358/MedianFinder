#include "rbt_median.h"
#include <assert.h>
#include <list>
#include <iomanip>

RBTMedian::RBTMedian()
{
}

RBTMedian::~RBTMedian()
{
}

void RBTMedian::add(int val) {
    if( _root == nullptr ) {
        _root = new RBNode(val, nullptr, RBNode::Color::Black);
    } else {
        Node *inserted = nullptr;
        insertInternal( _root, new RBNode( val, nullptr, RBNode::Color::Red ), &inserted );
        if( inserted != nullptr ) {
            fixRBTree( inserted );
            //printTree();
        }
    }
}

double RBTMedian::getMedian() {
    return BSTMedian::getMedian();
}

void RBTMedian::printTree(std::string filePath = "nodes.txt") {
    std::ofstream file( filePath, std::ios::app );
    if( file.is_open() ) {
        std::cout << "File opened! " << std::endl;
        std::list<RBNode*> parent;
        std::list<RBNode*> child;
        parent.push_back( static_cast<RBNode*>(_root) );
        bool empty = false;
        int limit = 100;
        while( !empty && limit ) {
            --limit;
            empty = true;
            for( const auto &node : parent ) {
                file << " ";
                if( node != nullptr ) {
                    file << node->value << ( node->c == RBNode::Color::Black ? "B" : "R" );
                    empty = false;
                    child.push_back( static_cast<RBNode*>(node->l) );
                    child.push_back( static_cast<RBNode*>(node->r) );
                } else {
                    file << "x";
                    child.push_back(nullptr);
                    child.push_back(nullptr);
                }
            }
            file << "\n";
            parent = child;
            child.clear();
        }
    }
    file.close();
}

/*           (xN)       <= rightRotate =     (yN)
*            /   \                           /   \
*               (yN)   = leftRotate =>   (xN)
*              /   \                    /   \
*/
void RBTMedian::rotate(Node *xN, RBTMedian::RotateType rt) {
    if( xN != nullptr ) {
        rt == RotateType::Left ? leftRotate( xN ) : rightRotate( xN );
    }
}

void RBTMedian::leftRotate(Node *xN) {
    if( xN->r != nullptr ) {
        Node *yN = xN->r;
        //Subtree
        xN->r = yN->l;
        if( yN->l != nullptr ) {
            yN->l->p = xN;
        }

        //Parents
        yN->p = xN->p;
        if( xN->p == nullptr ) {
            _root = yN;
        } else if( xN->p->l == xN ) {
            xN->p->l = yN;
        } else {
            xN->p->r = yN;
        }

        yN->l = xN;
        xN->p = yN;

        updateSubTreeSize( xN );
        updateSubTreeSize( yN );
    }
}

void RBTMedian::rightRotate(Node *xN) {
    if( xN->p != nullptr ) {
        Node *yN = xN->p;
        //Subtree
        yN->l = xN->r;
        if( xN->r != nullptr ) {
            xN->r->p = yN;
        }

        //Parents
        xN->p = yN->p;
        if( yN->p == nullptr ) {
            _root = xN;
        } else if( yN->p->l == yN ) {
            yN->p->l = xN;
        } else {
            yN->p->r = xN;
        }

        xN->r = yN;
        yN->p = xN;

        updateSubTreeSize( yN );
        updateSubTreeSize( xN );
    }
}

void RBTMedian::updateSubTreeSize( Node *node) {
    node->subTreeSize = 0;
    Node *nodes[2] = { node->l, node->r };
    for( int i = 0; i < 2; ++i ) {
        if( nodes[i] ) {
            node->subTreeSize += ( nodes[i]->subTreeSize + nodes[i]->size );
        }
    }
}

void RBTMedian::fixRBTree(Node *node) {
    while( node->p && RBNode::color(node->p) == RBNode::Color::Red ) {
        Node *grandP = grandParent( node );
        if( grandP ) {
            Node *u = uncle( node );
            if( u && RBNode::color(u) == RBNode::Color::Red ) {
                RBNode::color(node->p) = RBNode::Color::Black;
                RBNode::color(u) = RBNode::Color::Black;
                RBNode::color(grandP) = RBNode::Color::Red;
                node = grandP;
            } else {
                if( (node == node->p->r) && (node->p == grandP->l) ) {
                    rotate( node->p, RotateType::Left );
                    node = node->l;
                } else if( (node == node->p->l) && (node->p == grandP->r) ){
                    rotate( node, RotateType::Right );
                    node = node->r;
                }
                RBNode::color(node->p) = RBNode::Color::Black;
                RBNode::color(grandP) = RBNode::Color::Red;
                if( node == node->p->l ) {
                    rotate( node->p, RotateType::Right );
                } else {
                    rotate( grandP, RotateType::Left );
                }
            }            
        }
    }

    RBNode::color(_root) = RBNode::Color::Black;
}

BSTMedian::Node *RBTMedian::grandParent(Node *node) {
    if( node != nullptr && node->p ) {
        return node->p->p;
    } else {
        return nullptr;
    }
}

BSTMedian::Node *RBTMedian::uncle(Node *node) {
    Node *g = grandParent( node );
    if( !g ) {
        return nullptr;
    }

    if( node->p == g->l ) {
        return g->r;
    } else {
        return g->l;
    }
}

RBTMedian::RBNode::Color &RBTMedian::RBNode::color(BSTMedian::Node *n) {
    if( n ) {
        return static_cast<RBNode*>(n)->c;
    }
}
