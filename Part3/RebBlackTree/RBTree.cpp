#include<iostream>
#include"RBTree.h"
using namespace std;
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
    
    //tree->preOrder();
    tree->preOrder();
    //插入节点4
    tree->insert(4);
    tree->preOrder();
    

    cout <<"最小值" << tree->minimum() << endl;
    cout <<"最大值" << tree->maximum() << endl;
    //打印11的双子信息
    tree->search(11)->displayChild();

    //删除节点7
    tree->remove(7);
    tree->preOrder();
}