#include<iostream>
using namespace std;
/**
 * @brief 二叉搜索树的节点类
 */
template <class T>
class BSTNode{
    public:
        int key;
        BSTNode *parent;
        BSTNode *left;
        BSTNode *right;
    BSTNode(T value, BSTNode *p, BSTNode *l, BSTNode *r):
            key(value),parent(p),left(l),right(r) {}
        
};
//定义一个异常，当插入值已存在于树中时可以抛出 throw MyException()
class MyException:public exception
{
        public:
                const char* what()const throw()  
                {
                        return "The value to insert is already in the BSTree";
                }
};

        

/**
 * @brief 二叉搜索树类
 */
template <class T>
class BSTree{
    public:
        
        BSTNode<T> *root;

        T maximum();
        T minimum();
        BSTNode<T> *insert(T value);
        void preOrder();
    
    private:
        void insert(BSTNode<T>* &node, BSTNode<T> *z) const;
        void preOrder(BSTNode<T> *tree) const;
};





/**
 * @brief 将结点插入到二叉树中
 * @param tree  二叉树的根结点
 *        z     插入的结点
 */
template <class T>
void BSTree<T>::insert(BSTNode<T>* &tree, BSTNode<T>* z) const
{
    BSTNode<T> *y = NULL;
    BSTNode<T> *x = tree;

    // 查找z的插入位置
    while (x != NULL)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y==NULL)
        tree = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    
}

/**
 * @brief 将结点插入到二叉树中
 * @param key   要插入的值
 */
template <class T>
BSTNode<T>* BSTree<T>::insert(T key)
{
    BSTNode<T> *z=NULL;

    // 将值创建为一个节点，然后调用insert重载方法插入节点到树中
    if ((z=new BSTNode<T>(key,NULL,NULL,NULL)) == NULL)
        return NULL;

    insert(root, z);
    return z;
}
/**
 * @brief 前序遍历
 */
template <class T>
void BSTree<T>::preOrder(BSTNode<T> *tree) const{
    if(tree != NULL){
        cout << tree->key << " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T>
void BSTree<T>::preOrder(){
    preOrder(root);
}





