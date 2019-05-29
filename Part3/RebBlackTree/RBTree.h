#include<iostream>
using namespace std;

enum RBTColor{RED, BLACK};
/**
 * @brief 红黑树的节点类
 */
template <class T>
class RBTNode{
    public:
        int key;
        RBTNode *parent;
        RBTNode *left;
        RBTNode *right;
        void displayChild();
        RBTNode(T value, RBTNode *p, RBTNode *l, RBTNode *r):
            key(value),parent(p),left(l),right(r) {}
    
    private:
        void displayChild(RBTNode *left, RBTNode *right) const;
    
        
};