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
        //打印左右子节点的key与color信息
        void displayChild(){
            //打印左子
            if(left == NULL)    cout << "left: null null,";
            else                {cout << "left: "; left->display();}

            //打印右子
            if(left == NULL)    cout << " right: null null,";
            else                {cout << " right: "; right->display();}
            cout << endl;
            
        }
        //打印节点的key与color信息
        void display(){
            if(color == RED)    cout << key << " r,";
            else                cout << key << " b,";   
        }
        RBTNode( T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r):
            key(value), color(c), parent(p), left(l), right(r) {}
    
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

        T maximum();    //最大值
        T minimum();    //最小值
        
        RBTNode<T> *insert(T value);    //插入值到树中
        RBTNode<T> *search(T value);    //递归查找值
        RBTNode<T> *remove(T value);    //删除某值的节点


        void preOrder();       //先序遍历
        void inOrder();        //中序遍历
        void postOrder();      //后序遍历
        


    private:
        RBTNode<T> *maximum(RBTNode<T> *tree) const;      //最大值节点
        RBTNode<T> *minimum(RBTNode<T> *tree) const;      //最小值节点
        void leftRotate(RBTNode<T>* &root, RBTNode<T>* x) const;      //左旋
        void rightRotate(RBTNode<T>* &root, RBTNode<T>* y) const;     //右旋
        void insert(RBTNode<T>* &root, RBTNode<T>* z) const;          //插入节点到树中
        void insertFixUp(RBTNode<T>* &root, RBTNode<T>* z) const;     //插入后修复红黑树性质

        RBTNode<T> *search(RBTNode<T> *node, T value) const;    //递归查找值为value的节点

        void transplant(RBTNode<T>* &root, RBTNode<T> *u, RBTNode<T> *v) const;     //用v子树代替u子树
        RBTNode<T> *remove(RBTNode<T>* &root, RBTNode<T>* z) const;                 //删除节点z
        RBTNode<T> *removeFixUp(RBTNode<T>* &root, RBTNode<T>* x) const;            //删除后修复红黑树性质
        
        
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
 * @brief 查找最大值的节点
 * @param node  二叉树的根结点
 */
template <class T>
RBTNode<T> *RBTree<T>::maximum(RBTNode<T> *tree) const
{
    RBTNode<T> *p = tree;
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
T RBTree<T>::maximum()
{
    RBTNode<T> *node = maximum(root);
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
RBTNode<T> *RBTree<T>::minimum(RBTNode<T> *tree) const
{
    RBTNode<T> *p = tree;
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
T RBTree<T>::minimum()
{
    RBTNode<T> *node = minimum(root);
    if(node != NULL)
        return node->key;
    else
        return (T)NULL; 
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
        if(z->parent == z->parent->parent->left){
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
 * @brief 递归查找值对应的结点
 * @param node  二叉树的根节点
 *        z     key为要查找的值的节点
 */
template <class T>
RBTNode<T> *RBTree<T>::search(RBTNode<T> *node, T value) const
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
RBTNode<T> *RBTree<T>::search(T value){
    return search(root, value);
}

/**
 * @brief 用v子树替换u子树
 */
template <class T>
void RBTree<T>::transplant(RBTNode<T>* &root, RBTNode<T> *u, RBTNode<T> *v) const
{   
    //u为根
    if(u->parent == NULL)
        root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}
/**
 * @brief 删除某值的节点
 */
template <class T>
RBTNode<T> *RBTree<T>::remove(RBTNode<T>* &root, RBTNode<T>* z) const
{
    RBTNode<T> y = z;
    RBTColor y_origin_color = y->color;
    //x为可能变色的节点
    RBTNode<T> x;
    //左子为空，右子替代
    if( z->left == NULL){
        x = z->right;
        transplant(root, z, z->right);
    }
    //右子为空，左子替代
    else if(z->right == NULL){
        x = z->left;
        transplant(root, z, z->left);
    } 
    //双子非空，右子最小节点替代
    else{
        y = minimum(z->right);
        y_origin_color = y->color;
        x = y->right;

        //用z右子的最小节点替代z
        if(y->parent == z)
            x->parent = z;
        else{
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    //修复红黑性质
    if(y_origin_color == BLACK)
        removeFixUp(root, x);
} 
/**
 * @brief 删除某值的节点
 */                //删除节点z
template <class T>
RBTNode<T> *RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T>* x) const
{
    RBTNode<T> w = new RBTColor();
    while(x != root && x->color == BLACK){
        // x为左子
        if(x == x->parent->left){
            w = x->parent->right;
            // 情况1：兄弟为红
            if(w->color == RED){
                x->parent->color = RED;
                w->color = BLACK;
                leftRotate(root,x->parent);
                x = x->parent->right;
            }
            // 情况2：兄弟为黑，兄弟左右子为黑
            else if(w->left->color ==BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }
             // 情况3：兄弟为黑，兄弟左红右黑
            else if(w->right->color == BLACK){
                w->left->color = BLACK;
                w->color = RED;
                rightRotate(root, w);
                w = x->parent->right;
            }
            // 情况4：兄弟为黑，兄弟右子为红
            else{
                w->color = x->parent->color;
                x->parent->color = BLACK;
                leftRotate(root,x->parent);
                x = root;
            }
        }
        // x为左子
        else{
            w = x->parent->left;
            // 情况1：兄弟为红
            if(w->color == RED){
                x->parent->color = RED;
                w->color = BLACK;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            // 情况2：兄弟为黑，兄弟双子为黑
            else if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }
            // 情况3：兄弟为黑，兄弟左黑右红
            else if(w->left->color == BLACK){
                w->color = RED;
                w->right->color = BLACK;
                leftRotate(root, w);
                w = x->parent->left;
            }
            // 情况4：兄弟为黑，兄弟左子为红
            else{
                w->color = x->parent->color;
                x->parent->color = BLACK;
                rightRotate(root, x->parent);
                x = root;
            }

        }
    }
    x->color = BLACK;
    
}           

//删除后修复红黑树性质
/**
 * @brief 删除某值的节点
 */
template <class T>
RBTNode<T> *RBTree<T>::remove(T value){
    
    if(search(T) ==)
    
}
/**
 * @brief 先序遍历
 */
template <class T>
void RBTree<T>::preOrder(RBTNode<T>* tree) const
{
    if(tree != NULL){
        tree->display();
        preOrder(tree->left);
        
        preOrder(tree->right);
    }
}

template <class T>
void RBTree<T>::preOrder()
{
    cout << "先序遍历：";
    preOrder(root);
    cout << endl;
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