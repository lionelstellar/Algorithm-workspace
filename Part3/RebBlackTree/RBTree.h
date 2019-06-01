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


/**
 * @brief 红黑树
 * 1. 节点的颜色是红或黑
 * 2. 根和叶子是黑
 * 3. 红节点的两个子节点是黑的
 * 4. 任一节点到其所有后代叶节点的简单路径上，包含相同数目的黑色节点，该值为节点的黑高bh(x)
 */
template <class T>
class RBTree{
    public:
        RBTree();
        ~RBTree();
        RBTNode<T> *root;
    private:
        void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);      //左旋
        void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);     //右旋
};

/**
 * @brief 左旋
 * 
 *     Y       LEFT-ROTATE(T, X)       X
 *    / \    <--------------------    / \
 *   X   γ                           α   Y
 *  / \                                 / \
 * α   β                               β   γ 
 * 
 */
template <class T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
{
    RBTNode<T> *y = x->right;
    //右子为NULL，无法左旋
    if( y == NULL)
        return;

    //右子非NULL时进行三步操作
    //y的左子β，链接到x的右子
    x->right = y->left;
    if(y->left != NULL)
        y->left->parent = x;

    //将x的父节点作为y的父节点
    y->parent = x->parent;
    if(x->parent == NULL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    //x, y父子关系翻转
    y->left = x;
    x->parent = y;

}

/**
 * @brief 右旋
 * 
 *     Y       RIGHT-ROTATE(T, Y)      X
 *    / \    -------------------->    / \
 *   X   γ                           α   Y
 *  / \                                 / \
 * α   β                               β   γ 
 * 
 */
template <class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
    RBTNode<T> *x = y->left;
    //左子为NULL，无法右旋
    if( x == NULL)
        return;

    //左子非NULL时进行三步操作
    //x的右子β，链接为y的左子
    y->left = x->right;
    if(x->right != NULL)
        x->right->parent = y;

    //将y的父节点作为x的父节点
    x->parent = y->parent;
    if(y->parent == NULL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    

    //x, y父子关系翻转
    x->right = y;
    y->parent = x;


}