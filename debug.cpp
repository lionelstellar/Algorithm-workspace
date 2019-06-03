#include<iostream>
using namespace std;

enum RBTColor{RED, BLACK};
/**
 * @brief 红黑树的节点类
 */
template <class T>
class RBTNode{
    public:
        T key;
        RBTColor color;
        RBTNode *parent;
        RBTNode *left;
        RBTNode *right;
        void displayChild();
        void display(){
            if(color == RED)    cout << key << " r,";
            else                cout << key << " b,";   
        }
        RBTNode( T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r):
            key(value), color(c), parent(p), left(l), right(r) {}
    
    private:
        void displayChild(RBTNode *left, RBTNode *right) const; 
};




/**
 * @brief 红黑树
 * 1. 节点的颜色是红或黑
 * 2. 根是黑色
 * 3. 叶子是黑色
 * 3. 红节点的两个子节点是黑的
 * 4. 任一节点到其所有后代叶节点的简单路径上，包含相同数目的黑色节点，该值为节点的黑高bh(x)
 */
template <class T>
class RBTree{
    public:
        RBTree();
        ~RBTree();
        RBTNode<T> *root;
        
        RBTNode<T> *insert(T value);    //插入值到树中


        void preOrder();       //先序遍历
        void inOrder();        //中序遍历
        void postOrder();      //后序遍历
        


    private:
        void leftRotate(RBTNode<T>* &root, RBTNode<T>* x) const;      //左旋
        void rightRotate(RBTNode<T>* &root, RBTNode<T>* y) const;     //右旋
        void insert(RBTNode<T>* &root, RBTNode<T>* z) const;          //插入节点到树中
        void insertFixUp(RBTNode<T>* &root, RBTNode<T>* z) const;     //插入后修复红黑树性质

        void preOrder(RBTNode<T>* tree) const;       //先序遍历
        void inOrder(RBTNode<T>* tree) const;        //中序遍历
        void postOrder(RBTNode<T>* tree) const;      //后序遍历
};

// 构造函数
template <class T>
RBTree<T>::RBTree(){
    root = NULL;
}

// 析构函数
template <class T>
RBTree<T>::~RBTree(){
    if(root == NULL)
        return;
    FreeMemory(root);
}

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
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x) const
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
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y) const
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
/**
 * @brief 将已结点插入到红黑树中的节点修复红黑性质
 * @param root  二叉树的根结点
 *        z     插入的结点
 */
template <class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* z) const
{
    RBTNode<T> *y;
    while(z->parent && z->parent->color == RED){
        // z.p是一个其父的左子
        if(z->parent == z->parent->left){
            // y为叔节点
            y = z->parent->parent->right;
            // 情况1：叔也为红
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
            
                z = z->parent->parent;
            }
            // 情况2：叔为黑，z为右子
            else if(z == z->parent->right){
                z = z->parent;
                leftRotate(root, z);
            }
            // 情况3：叔为黑，z为左子
            else{
                z->parent->parent->color = RED;
                z->parent->color = BLACK;
                rightRotate(root, z->parent->parent); 
            }
        }
        // z.p是其父的右子
        else{
            // y为叔节点
            y = z->parent->parent->left;
            // 情况1：叔也为红
            if(y->color == RED){
                y->color = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            }
            else{
                // 情况2：z为左子
                if(z == z->parent->left){
                    z = z->parent;
                    rightRotate(root, z);
                }
                // 情况3：z为右子
                else{
                    z->parent->parent->color = RED;
                    z->parent->color = BLACK;
                    leftRotate(root,z->parent->parent);
                }
            }
        }
        
    }
    root->color = BLACK;

}

/**
 * @brief 将结点插入到红黑树中，保持二叉搜索树的性质
 * @param root  二叉树的根结点
 *        z     插入的结点
 */
template <class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T> *z) const
{
    RBTNode<T> *y = NULL;
    RBTNode<T> *x = root;
    while(x != NULL){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else if(z->key > x->key)
            x = x->right;
    }

    z->parent = y;
    if(y == NULL)
        root = z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;
    
    insertFixUp(root, z);

} 


/**
 * @brief 将值插入到红黑树中
 * @param key   要插入的值
 */
template <class T>
RBTNode<T> *RBTree<T>::insert(T key)
{
    RBTNode<T> *z = new RBTNode<T>(key, RED, NULL, NULL, NULL);
    if(z == NULL)
        return NULL;
    insert(root,z);
    return z;
}



/**
 * @brief 中序遍历
 */
template <class T>
void RBTree<T>::inOrder(RBTNode<T>* tree) const
{
    if(tree != NULL){
        inOrder(tree->left);
        tree->display();
        inOrder(tree->right);
    }
}

template <class T>
void RBTree<T>::inOrder()
{
    cout << "中序遍历：";
    inOrder(root);
    cout << endl;
}

int main()
{
    // arr为要插入的元素
    int arr[] = {11,2,14,1,7,5,8,15};
    // 建树
    RBTree<int> *tree = new RBTree<int>();
    
    
    
     //将元素循环插入树中
    for(int i = 0; i < sizeof(arr)/sizeof(int); i++){
        tree->insert(arr[i]);
    }
    

    tree->inOrder();
}