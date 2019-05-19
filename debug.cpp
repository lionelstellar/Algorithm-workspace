#include<iostream>
using namespace std;

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
//定义一个异常，当插入值已存在于树中时可以抛出
class MyException:public exception
{
        public:
                const char* what()const throw()  
                //函数后面必须跟throw(),括号里面不能有任务参数，表示不抛出任务异常
                //因为这个已经是一个异常处理信息了，不能再抛异常。
                {
                        return "The value to insert is already in the BSTree";
                }
};

        



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




/*
template <class T>
BSTNode<T> *BSTree<T>::insert(BSTNode<T> *tree, BSTNode<T> *z) const{
    
    BSTNode<T> *x = tree;
    BSTNode<T> *y;
    while(x != NULL){
        y = x;
        while( x != NULL){
            if(z->key == x->key){
                throw MyException();
            }
            else if(z->key < x->key){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }
        z->parent = y;
    }
    //
    if(y == NULL){
        root->key = z->key;
        return root;
    }
    
    if(z->key < y->key){
        y->left = z;
    }
    else{
        y->right = z;
    }
    return z;

}

template <class T>
BSTNode<T> *BSTree<T>::insert(T key)
{
    BSTNode<T> *z=NULL;

    // 如果新建结点失败，则返回。
    if ((z=new BSTNode<T>(key,NULL,NULL,NULL)) == NULL)
        return NULL;

    return insert(root, z);
}
*/
/* 
 * 将结点插入到二叉树中
 *
 * 参数说明：
 *     tree 二叉树的根结点
 *     z 插入的结点
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
        if(z->key < x->key)
            x = x->left;
        else if(z->key > x->key)
            x = x->right;
        else
        {
            throw MyException();
        }
        
    }

    z->parent = y;
    if (y==NULL)
        tree = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    
}

/* 
 * 将结点(key为节点键值)插入到二叉树中
 *
 * 参数说明：
 *     tree 二叉树的根结点
 *     key 插入结点的键值
 */
template <class T>
BSTNode<T>* BSTree<T>::insert(T key)
{
    BSTNode<T> *z=NULL;

    // 如果新建结点失败，则返回。
    if ((z=new BSTNode<T>(key,NULL,NULL,NULL)) == NULL)
        return NULL;

    insert(root, z);
    return z;
}





int main(){
    BSTNode<int> b2(2,NULL, NULL, NULL);
    BSTNode<int> b3(3,NULL, NULL, NULL);
    BSTNode<int> b1(1,&b3, &b2, NULL);
    
    //arr为要排序的数组
    //int arr[] = {5,2,4,7,10,9,8,1,6,3};
    int arr[] = {1,1};
    //建树
    BSTree<int>* tree=new BSTree<int>();
    //tree->insert(1);
    //tree->preOrder();
    
    for(int i = 0; i < sizeof(arr)/sizeof(int); i++){
        //cout << arr[i] << " ";
        tree->insert(arr[i]);
    }
    tree->preOrder();
    

}
