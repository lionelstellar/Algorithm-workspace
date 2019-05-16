#include<iostream>
using namespace std;

template <class t>
class BSNode{
    public:
        int key;
        BSNode *parent;
        BSNode *left;
        BSNode *right;
    BSNode(t key, BSNode *parent, BSNode *left, BSNode *right):
        key(value),parent(),left(l),right(r) {}
};