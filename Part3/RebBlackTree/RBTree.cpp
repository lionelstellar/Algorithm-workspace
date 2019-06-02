#include<iostream>
#include"RBTree.h"

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
}