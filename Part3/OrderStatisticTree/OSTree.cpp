#include<iostream>
#include"OSTree.h"
using namespace std;
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
    cout << tree->OS_rank(tree->search(8)) << endl;
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