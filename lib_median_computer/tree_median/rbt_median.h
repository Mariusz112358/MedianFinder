#ifndef RBTMEDIAN_H
#define RBTMEDIAN_H
#include "../imedian_computer.h"
#include "bst_median.h"
#include <iostream>
#include <fstream>

class RBTMedian : public BSTMedian
{
public:
    RBTMedian();
    ~RBTMedian();

    void add(int val) final override;
    double getMedian() final override;

    void printTree(std::string filePath);
private:
    struct RBNode : public BSTMedian::Node {
        enum class Color {
            Red,
            Black
        };

        RBNode( int v, RBNode *par, Color clr ) :
            Node::Node(v,par),
            c(clr)
        {
        }
        ~RBNode() {}        
        Color c;
        static Color& color( Node *n );
        static void setColor(Node *n , Color c);
    };

    enum class RotateType {
        Left,
        Right
    };

    void rotate(Node *xN, RotateType rt );
        void leftRotate( Node *xN );
        void rightRotate(Node *xN );
            void updateSubTreeSize(Node *node );

    void fixRBTree(Node *node );
        Node *grandParent(Node *node );
        Node *uncle(Node *node );
};

#endif // RBTMEDIAN_H
