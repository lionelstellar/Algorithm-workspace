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

template <class T>
class BSTree{
    public:
        
        BSTNode<T> *root;

        T maximum();
        T minimum();
        BSTNode<T> *insert(T value);
        void inorder();
};

template <class T>
BSTNode<T> *BSTree<T>::insert(T value){
    BSTNode<T> *x = root;

}


int main(){
    BSTNode<int> b2(2,nullptr, nullptr, nullptr);
    BSTNode<int> b3(3,nullptr, nullptr, nullptr);
    BSTNode<int> b1(1,&b3, &b2, nullptr);
    
    cout << b1.parent->key << endl;
    BSTNode<int> *b = &b1;
    cout << b->left->key << endl;
}