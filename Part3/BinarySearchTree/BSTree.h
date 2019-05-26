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
        void displayChild();
        BSTNode(T value, BSTNode *p, BSTNode *l, BSTNode *r):
            key(value),parent(p),left(l),right(r) {}
    
    private:
        void displayChild(BSTNode *left, BSTNode *right) const;
    
        
};
template <class T>
void BSTNode<T>::displayChild(BSTNode *left, BSTNode *right) const{
    if(left == NULL)
        cout<< "left is NULL,";
    else
        cout<<"left is " << left->key <<","; 
    
    if(right == NULL)
        cout<< "right is NULL";
    else
        cout<<"right is " << right->key; 
    cout << endl;
    
}
template <class T>
void BSTNode<T>::displayChild(){
    displayChild(left, right);
}



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
        BSTree();
        ~BSTree();
        
        BSTNode<T> *root;

        T maximum();    //最大值
        T minimum();    //最小值
        BSTNode<T> *insert(T value);    //插入值到树中
        BSTNode<T> *search(T value);    //递归查找值
        BSTNode<T> *iterativeSearch(T value); //迭代查找值
        BSTNode<T> *remove(T value);    //删除值

        
        BSTNode<T>* successor(BSTNode<T> *x);   //找到比该节点大的最小值
        BSTNode<T>* predecessor(BSTNode<T> *x); //找到比该节点小的最大值

        void preOrder();    //先序遍历
        void inOrder();     //中序遍历
        void postOrder();   //后序遍历
    
    private:
        BSTNode<T> *maximum(BSTNode<T> *tree) const;      //最大值节点
        BSTNode<T> *minimum(BSTNode<T> *tree) const;      //最小值节点
        void insert(BSTNode<T>* &root, BSTNode<T>* z) const;     //插入节点到树中
        BSTNode<T> *search(BSTNode<T> *node, T value) const;    //递归查找值为value的节点
        BSTNode<T> *iterativeSearch(BSTNode<T>* &root, T value) const;    //迭代查找值为value的节点
        void remove(BSTNode<T>* &root, BSTNode<T>* z) const;    //删除节点z
        
        BSTNode<T>* successor(BSTNode<T> *tree, BSTNode<T> *x) const;   //找到比该节点大的最小值
        BSTNode<T>* predecessor(BSTNode<T> *tree, BSTNode<T> *x) const; //找到比该节点小的最大值
        
        void preOrder(BSTNode<T> *tree) const;  //先序遍历
        void inOrder(BSTNode<T> *tree) const;   //中序遍历
        void postOrder(BSTNode<T> *tree) const; //后序遍历
        
};

// 构造函数
template <class T>
BSTree<T>::BSTree(){
    root = NULL;
}

// 析构函数
template <class T>
BSTree<T>::~BSTree(){
    if(root == NULL)
        return;
    FreeMemory(root);
}

/**
 * @brief 查找最大值的节点
 * @param node  二叉树的根结点
 */
template <class T>
BSTNode<T> *BSTree<T>::maximum(BSTNode<T> *tree) const
{
    BSTNode<T> *p = tree;
    while(p->right != NULL){
        p = p->right;
    }
    if(p == NULL)
        return NULL;
    else
        return p;
}
/**
 * @brief 查找最大值
 */
template <class T>
T BSTree<T>::maximum()
{
    BSTNode<T> *node = maximum(root);
    if(node != NULL)
        return node->key;
    else
        return (T)NULL; 
}

/**
 * @brief 查找最小值的节点
 * @param node  二叉树的根结点
 */
template <class T>
BSTNode<T> *BSTree<T>::minimum(BSTNode<T> *tree) const
{
    BSTNode<T> *p = tree;
    while(p->left != NULL){
        p = p->left;
    }
    if(p == NULL)
        return NULL;
    else
        return p;
}
/**
 * @brief 查找最小值
 */
template <class T>
T BSTree<T>::minimum()
{
    BSTNode<T> *node = minimum(root);
    if(node != NULL)
        return node->key;
    else
        return (T)NULL; 
}


/**
 * @brief 将结点插入到二叉树中
 * @param node  二叉树的根结点
 *        z     插入的结点
 */
template <class T>
void BSTree<T>::insert(BSTNode<T>* &root, BSTNode<T>* z) const
{
    BSTNode<T> *y = NULL;
    BSTNode<T> *x = root;

    // 查找z的插入位置
    while (x != NULL)
    {
        y = x;
        
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
        //如果要设置不允许插入相同的值,整个循环体可改为下段注释中的代码
        /*
        y = x;
        if(z->key < x->key)
            x = x->left;
        else if(z->key > x->key)
            x = x->right;
        else
        {
            throw MyException();
        }
        */
    }

    z->parent = y;
    if (y==NULL)
        root = z;
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
BSTNode<T> *BSTree<T>::insert(T key)
{
    BSTNode<T> *z=NULL;

    // 将值创建为一个节点，然后调用insert重载方法插入节点到树中
    if ((z=new BSTNode<T>(key,NULL,NULL,NULL)) == NULL)
        return NULL;

    insert(root, z);
    return z;
}
/**
 * @brief 迭代查找值对应的结点
 * @param root  二叉树的根节点
 *        z     key为要查找的值的节点
 */
template <class T>
BSTNode<T> *BSTree<T>::iterativeSearch(BSTNode<T>* &root, T value) const
{
    BSTNode<T> *z = new BSTNode<T>(value, NULL, NULL, NULL);
    BSTNode<T> *node = root;
    while(node != NULL){
        if(node->key == value){
            z = node;
            return z;
        }
        else if(node->key < value)
            node = node->right;
        else
            node = node->left;    
    }  
    
    return NULL;
}

/**
 * @brief 迭代查找值对应的结点
 * @param value   要查找的值
 */
template <class T>
BSTNode<T> *BSTree<T>::iterativeSearch(T value){
    
    return iterativeSearch(root, value);
    
}
/**
 * @brief 递归查找值对应的结点
 * @param node  二叉树的根节点
 *        z     key为要查找的值的节点
 */
template <class T>
BSTNode<T> *BSTree<T>::search(BSTNode<T> *node, T value) const
{
    if(node == NULL || node->key == value){
        return node;
    }
        
    else if(node->key > value){
        return search(node->left, value);
    }
        
    else{
        return search(node->right, value);
    }
        
}
/**
 * @brief 递归查找值对应的结点
 * @param value   要查找的值
 */
template <class T>
BSTNode<T> *BSTree<T>::search(T value){
    return search(root, value);
}
/**
 * @brief 找到比该节点大的最小值
 * @param tree  树
 *        value 值
 */
template <class T>
BSTNode<T>* BSTree<T>::successor(BSTNode<T> *tree, BSTNode<T> *x) const
{
    if(x->right != NULL){
        return minimum(x->right);
    }
    BSTNode<T> *y = x->parent;
    while ((y!=NULL) && (x==y->right))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

/**
 * @brief 找到比该节点大的最小值
 * @param value 值
 */
template <class T>
BSTNode<T>* BSTree<T>::successor(BSTNode<T> *x){
    return successor(root, x);
}   

/**
 * @brief 找到比该节点小的最大值
 * @param tree  树
 *        value 值
 */
template <class T>
BSTNode<T>* BSTree<T>::predecessor(BSTNode<T> *tree, BSTNode<T> *x) const
{
    if(x->left != NULL){
        return maximum(x->left);
    }
    
    BSTNode<T> *y = x->parent;
    while((y != NULL) && (x == y->left)){
        x = y;
        y = y->parent;
    }
    return y;
}

/**
 * @brief 找到比该节点小的最大值
 * @param value 值
 */
template <class T>
BSTNode<T>* BSTree<T>::predecessor(BSTNode<T> *x){
    return predecessor(root, x);
}   
        
        
        



/**
 * @brief 先序遍历
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
    cout << "先序遍历：";
    preOrder(root);
    cout << endl;
}

/**
 * @brief 中序遍历
 */
template <class T>
void BSTree<T>::inOrder(BSTNode<T> *tree) const{
    if(tree != NULL){
        inOrder(tree->left);
        cout << tree->key << " ";
        inOrder(tree->right);
    }
}

template <class T>
void BSTree<T>::inOrder(){
    cout << "中序遍历：";
    inOrder(root);
    cout << endl;
}

/**
 * @brief 后序遍历
 */
template <class T>
void BSTree<T>::postOrder(BSTNode<T> *tree) const{
    if(tree != NULL){
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->key << " ";
    }
}

template <class T>
void BSTree<T>::postOrder(){
    cout << "后序遍历：";
    postOrder(root);
    cout << endl;
}

template <class T>
void BSTree<T>::remove(BSTNode<T> *&root, BSTNode<T> *z) const
{
    BSTNode<T> *p = z;
    while(p != NULL){
        if(p->left == NULL && p->right == NULL){
            if(p == p->parent->left)
                p->parent->left = NULL;
            else
                p->parent->right = NULL;
            p = NULL;    
        }
        else if(p->left != NULL && p->right == NULL){
            p->key = p->left->key;
            p = p->left;
        }
        else if(p->left != NULL && p->right != NULL){
            p->key = p->right->key;
            p = p->right;
        }
    }
    
}

template <class T>
BSTNode<T> *BSTree<T>::remove(T value)
{
    BSTNode<T> *z = search(value);
    if(z == NULL)
        return NULL;
    else
        remove(root, z);
        return z;
      
}