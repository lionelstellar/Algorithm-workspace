#include<iostream>
#include"BSTree.h"
using namespace std;

int main(){
    
    //arr为要排序的数组
    int arr[] = {5,2,4,7,10,9,8,1,6,3};
    //建树
    BSTree<int>* tree=new BSTree<int>();
    
    //将数组中的树循环插入二叉搜索树中
    for(int i = 0; i < sizeof(arr)/sizeof(int); i++){
        //cout << arr[i] << " ";
        tree->insert(arr[i]);
    }

    
    
    //先序遍历
    tree->preOrder();
    //中序遍历
    tree->inOrder();
    //后序遍历
    tree->postOrder();
    
    //查找
    int value = 50;
    BSTNode<int> *node = tree->search(value);
    if(node != NULL)
        cout << node->left->key << " " << node->right->key << endl;
    else
    {
        cout << value << " is not in the tree" << endl;
    }

    //最大最小值
    int max = tree->maximum();
    cout <<"max: " << max << endl;
    int min = tree->minimum();
    cout <<"min: " << min << endl;

    tree->remove(5);
    tree->preOrder();
    tree->inOrder();

}