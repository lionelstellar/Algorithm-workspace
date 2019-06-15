#include<iostream>
#include<vector>
using namespace std;

enum OSTColor {BLACK, RED};

/**
 * @brief 顺序统计树的节点类
 */
template <class T>
class OSTNode{
    public:
        T key;
        OSTNode *parent;
        OSTNode *left;
        OSTNode *right;
        OSTColor color;
        int size;

        //打印左右子节点的key、color、size信息
        void displayChild(){
            //打印左子
            if(left == NULL)    cout << "left: null null ( null ),";
            else                {cout << "left: "; left->display();}

            //打印右子
            if(left == NULL)    cout << " right: null null  ( null ),";
            else                {cout << " right: "; right->display();}
            cout << endl;
            
        }
        //打印节点的key与color信息
        void display(){
            if(color == RED)    cout << key << " r" << " ( " << size << " ),";
            else                cout << key << " b" << " ( " << size << " ),";   
        }

        OSTNode(T value, OSTColor c, OSTNode *p, OSTNode *l, OSTNode *r,  int s):
            key(value),color(c),parent(p),left(l),right(r),size(s) {}


};

/**
 * @brief 顺序统计树
 * 增加了节点size信息的顺序统计树
 * x.size = x.left.size + x.right.size + 1;
 * NIL.size = 0;
 */
template <class T>
class OSTree{
    public:
        OSTree();
        ~OSTree();

        OSTNode<T> *root;
        OSTNode<T> *NIL;

        T maximum();    //最大值
        T minimum();    //最小值
        
        OSTNode<T> *OS_insert(T value);    //插入值到树中
        OSTNode<T> *search(T value);       //递归查找值
        OSTNode<T> *OS_select(int rank);   //查找第i小的值,即秩为i的节点
        OSTNode<T> *OS_remove(T value);    //删除某值的节点


        void preOrder();       //先序遍历
        void inOrder();        //中序遍历
        void postOrder();      //后序遍历
        


    private:
        OSTNode<T> *maximum(OSTNode<T> *tree) const;      //最大值节点
        OSTNode<T> *minimum(OSTNode<T> *tree) const;      //最小值节点
        void OS_leftRotate(OSTNode<T>* &root, OSTNode<T>* x) const;      //左旋
        void OS_rightRotate(OSTNode<T>* &root, OSTNode<T>* y) const;     //右旋
        void OS_insert(OSTNode<T>* &root, OSTNode<T>* z) const;          //插入节点到树中
        void OS_insertFixUp(OSTNode<T>* &root, OSTNode<T>* z) const;     //插入后修复顺序统计树性质

        OSTNode<T> *search(OSTNode<T> *node, T value) const;             //递归查找值为value的节点
        OSTNode<T> *OS_select(OSTNode<T> *node, int rank) const;         //查找第i小的值,即秩为i的节点

        void OS_transplant(OSTNode<T>* &root, OSTNode<T> *u, OSTNode<T> *v) const;     //用v子树代替u子树
        void OS_remove(OSTNode<T>* &root, OSTNode<T>* z) const;                 //删除节点z
        void OS_removeFixUp(OSTNode<T>* &root, OSTNode<T>* x) const;            //删除后修复顺序统计树性质
        
        
        void preOrder(OSTNode<T>* tree) const;       //先序遍历
        void inOrder(OSTNode<T>* tree) const;        //中序遍历
        void postOrder(OSTNode<T>* tree) const;      //后序遍历
};

// 构造函数
template <class T>
OSTree<T>::OSTree(){
    NIL = new OSTNode<T>(T(NULL),BLACK,NULL,NULL,NULL,0);
    root = NIL;
}

// 析构函数
template <class T>
OSTree<T>::~OSTree(){
    if(root == NIL)
        return;
    FreeMemory(root);
}
/**
 * @brief 查找最大值的节点
 * @param tree 根结点
 */
template <class T>
OSTNode<T> *OSTree<T>::maximum(OSTNode<T> *tree) const
{
    OSTNode<T> *p = tree;
    while(p->right != NIL){
        p = p->right;
    }
    if(p == NIL)
        return NIL;
    else
        return p;
}
/**
 * @brief 查找最大值
 */
template <class T>
T OSTree<T>::maximum()
{
    OSTNode<T> *node = maximum(root);
    if(node != NIL)
        return node->key;
    else
        return (T)NULL; 
}
/**
 * @brief 查找最小值的节点
 * @param node  二叉树的根结点
 */
template <class T>
OSTNode<T> *OSTree<T>::minimum(OSTNode<T> *tree) const
{
    OSTNode<T> *p = tree;
    while(p->left != NIL){
        p = p->left;
    }
    if(p == NIL)
        return NIL;
    else
        return p;
}
/**
 * @brief 查找最小值
 */
template <class T>
T OSTree<T>::minimum()
{
    OSTNode<T> *node = minimum(root);
    if(node != NIL)
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
void OSTree<T>::OS_leftRotate(OSTNode<T>* &root, OSTNode<T>* x) const
{
    OSTNode<T> *y = x->right;
    //右子为NIL，无法左旋
    if( y == NIL)
        return;

    //右子非NIL时进行三步操作
    //y的左子β，链接到x的右子
    x->right = y->left;
    if(y->left != NIL)
        y->left->parent = x;

    //将x的父节点作为y的父节点
    y->parent = x->parent;
    if(x->parent == NIL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    //x, y父子关系翻转
    y->left = x;
    x->parent = y;

    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;

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
void OSTree<T>::OS_rightRotate(OSTNode<T>* &root, OSTNode<T>* y) const
{
    OSTNode<T> *x = y->left;
    //左子为NIL，无法右旋
    if( x == NIL)
        return;

    //左子非NIL时进行三步操作
    //x的右子β，链接为y的左子
    y->left = x->right;
    if(x->right != NIL)
        x->right->parent = y;

    //将y的父节点作为x的父节点
    x->parent = y->parent;
    if(y->parent == NIL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    

    //x, y父子关系翻转
    x->right = y;
    y->parent = x;

    x->size = y->size;
    y->size = y->left->size + y->right->size + 1;


}
/**
 * @brief 将已结点插入到顺序统计树中的节点修复顺序统计性质
 * @param root  二叉树的根结点
 *        z     插入的结点
 */
template <class T>
void OSTree<T>::OS_insertFixUp(OSTNode<T>* &root, OSTNode<T>* z) const
{
    OSTNode<T> *y;
    while(z->parent != NIL && z->parent->color == RED){
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
                OS_leftRotate(root, z);
            }
            // 情况3：叔为黑，z为左子
            else{
                z->parent->parent->color = RED;
                z->parent->color = BLACK;
                OS_rightRotate(root, z->parent->parent); 
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
                    OS_rightRotate(root, z);
                }
                // 情况3：z为右子
                else{
                    z->parent->parent->color = RED;
                    z->parent->color = BLACK;
                    OS_leftRotate(root,z->parent->parent);
                }
            }
        }
        
    }
    root->color = BLACK;

}

/**
 * @brief 将结点插入到顺序统计树中，保持二叉搜索树的性质
 * @param root  二叉树的根结点
 *        z     插入的结点
 */
template <class T>
void OSTree<T>::OS_insert(OSTNode<T>* &root, OSTNode<T> *z) const
{
    OSTNode<T> *y = NIL;
    OSTNode<T> *x = root;
    
    while(x != NIL){
        y = x;
        x->size = x->size + 1;
        if(z->key < x->key)
            x = x->left;
        //顺序统计🌲不再要求关键字各不相同
        else if(z->key >= x->key)
            x = x->right;
    }

    z->parent = y;
    if(y == NIL)
        root = z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;
    
    
    OS_insertFixUp(root, z);

} 


/**
 * @brief 将值插入到顺序统计树中
 * @param key   要插入的值
 */
template <class T>
OSTNode<T> *OSTree<T>::OS_insert(T key)
{
    OSTNode<T> *z = new OSTNode<T>(key, RED, NULL, NIL, NIL, 1);
    if(z == NULL)
        return NULL;
    OS_insert(root,z);
    return z;
}






/**
 * @brief 递归查找值对应的结点
 * @param node  二叉树的根节点
 *        z     key为要查找的值的节点
 */
template <class T>
OSTNode<T> *OSTree<T>::search(OSTNode<T> *node, T value) const
{
    if(node == NIL || node->key == value){
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
OSTNode<T> *OSTree<T>::search(T value){
    return search(root, value);
}

/**
 * @brief 查找秩为rank的节点
 * @param   node   要查找的树的根
 *          rank   要查找的秩
 */
template <class T>
OSTNode<T> *OSTree<T>::OS_select(OSTNode<T> *node, int rank) const
{
    while(rank != node->left->size + 1){
        if(rank < node->left->size + 1){
            node = node->left;
        }
        else{
            node = node->right;
            rank = rank - (node->left->size + 1);
        }
    }
    
}
/**
 * @brief 查找秩为rank的节点
 * @param rank   要查找的秩
 */
template <class T>
OSTNode<T> *OSTree<T>::OS_select(int rank){
    //秩超出了树的大小
    if(rank > root->size){
        return (OSTNode<T>)NULL;
    }
    return OS_select(root, rank);
}

/**
 * @brief 用v子树替换u子树
 */
template <class T>
void OSTree<T>::OS_transplant(OSTNode<T>* &root, OSTNode<T> *u, OSTNode<T> *v) const
{   
    //u为根
    if(u->parent == NIL)
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
void OSTree<T>::OS_remove(OSTNode<T>* &root, OSTNode<T>* z) const
{
    OSTNode<T> *y = z;
    OSTColor y_origin_color = y->color;
    //x为可能变色的节点
    OSTNode<T> *x = new OSTNode<T>(0,RED,NULL,NULL,NULL);
    //左子为空，右子替代
    if( z->left == NIL){
        x = z->right;
        transplant(root, z, z->right);
    }
    //右子为空，左子替代
    else if(z->right == NIL){
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
    //修复顺序统计性质
    if(y_origin_color == BLACK)
        removeFixUp(root, x);
} 
/**
 * @brief 删除某值的节点
 */                //删除节点z
template <class T>
void OSTree<T>::OS_removeFixUp(OSTNode<T>* &root, OSTNode<T>* x) const
{
    OSTNode<T> *w;
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

//删除后修复顺序统计树性质
/**
 * @brief 删除某值的节点
 */
template <class T>
OSTNode<T> *OSTree<T>::OS_remove(T value){
    OSTNode<T> *node = search(value);
    if(node != NIL)
        remove(root, node);
        
    return node;
}
/**
 * @brief 先序遍历
 */
template <class T>
void OSTree<T>::preOrder(OSTNode<T>* tree) const
{
    if(tree != NIL){
        tree->display();
        preOrder(tree->left);
        
        preOrder(tree->right);
    }
}

template <class T>
void OSTree<T>::preOrder()
{
    cout << "先序遍历：";
    preOrder(root);
    cout << endl;
}


/**
 * @brief 中序遍历
 */
template <class T>
void OSTree<T>::inOrder(OSTNode<T>* tree) const
{
    if(tree != NIL){
        inOrder(tree->left);
        tree->display();
        inOrder(tree->right);
    }
}

template <class T>
void OSTree<T>::inOrder()
{
    cout << "中序遍历：";
    inOrder(root);
    cout << endl;
}

/**
 * @brief 后序遍历
 */
template <class T>
void OSTree<T>::postOrder(OSTNode<T>* tree) const
{
    if(tree != NIL){
        postOrder(tree->left);
        
        postOrder(tree->right);
        tree->display();
    }
}

template <class T>
void OSTree<T>::postOrder()
{
    cout << "后序遍历：";
    postOrder(root);
    cout << endl;
}

int main()
{
    //OSTNode<int> *NIL = new OSTNode<int>(NULL,BLACK,NULL,NULL,NULL,0);
    // arr为要插入的元素
    int arr[] = {11,2,14,1,7,5,8,15};
    // 建树
    OSTree<int> *tree = new OSTree<int>();
    
    
    
     //将元素循环插入树中
    for(int i = 0; i < sizeof(arr)/sizeof(int); i++){
        tree->OS_insert(arr[i]);
    }
    
    //tree->preOrder();
    tree->preOrder();
    /*
    //插入节点4
    tree->OS_insert(4);
    tree->preOrder();
    

    cout <<"最小值" << tree->minimum() << endl;
    cout <<"最大值" << tree->maximum() << endl;
    //打印11的双子信息
    tree->search(11)->displayChild();

    //删除节点7
    tree->OS_remove(7);

    //后序遍历
    tree->postOrder();
     */
}