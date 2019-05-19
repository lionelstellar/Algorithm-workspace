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
    

}