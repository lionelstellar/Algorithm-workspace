#include<iostream>
#include"BSTree.h"
using namespace std;

int main(){
    BSTNode<int> b2(2,NULL, NULL, NULL);
    BSTNode<int> b3(3,NULL, NULL, NULL);
    BSTNode<int> b1(1,&b3, &b2, NULL);
    
    //arr为要排序的数组
    int arr[] = {5,2,4,7,10,9,8,1,6,3,3};
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