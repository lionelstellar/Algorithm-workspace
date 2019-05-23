#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
//尾插法创建链表
 ListNode *create_linklist(int *arr, int n)
 {
     ListNode *head = new ListNode(arr[0]);
     ListNode *p = head;
     for(int i = 1; i < n; i++){
         ListNode *q = new ListNode(arr[i]);
         p->next = q;
         p = q;
     }
     return head;
 }

//三个内联函数，用来求每个节点的父、左子、右子节点
inline int left(int parent)
{
    return parent << 1;
}

inline int right(int parent)
{
    return 1 + (parent << 1);
}

inline int parent(int child)
{
    return child >> 1;
}

//维护最小堆的性质
void Min_Heapify(vector<ListNode *> &v, int i)
{
    int size = v.size() - 1;   
    int least;
    int l = left(i);
    int r = right(i);
    //左子小于父节点,least = l
    if(l <= size && v[l]->val < v[i]->val)    
        least = l;
    else                            
        least = i;
    
    //least取右子和左子、父中的较小值节点
    if(r <= size && v[r]->val < v[least]->val){
        least = r;
    }

    if(least != i){
        swap(v[i],v[least]);
        Min_Heapify(v,least);
    }
}

//从最小parent节点往上维护最小堆性质，就能形成最小堆
void Build_Min_Heap(vector<ListNode *> &v)
{   
    //最后一个子节点v.size()/2向下取整是号码最小的parent节点，所以直接从这里count down
    for(int i = v.size()/2; i > 0; i--)
    {
        Min_Heapify(v,i);
    }
}
//打印链表
void display(ListNode *l){
    while(l!=NULL){
        cout << l->val << " ";
        l = l->next;
    }
    cout << endl;
}

//k-merge
vector<int> k_merge(ListNode **L, int k){
    vector<ListNode *> minheap;
    vector<int> ret;
    
    
    //将非空链表的每一个头部值取出
    minheap.push_back(NULL);
    for(int i = 0; i < k; i++){
        if(L[i] == NULL)
            k--;
        else
            minheap.push_back(L[i]);
    }
    
    //建堆
    Build_Min_Heap(minheap);
    //只要剩余链表多余1就循环
    while(k > 1){
        
        ret.push_back(minheap[1]->val);
        minheap[1] = minheap[1]->next;
        
        //根上的链表所有元素被取完
        if(minheap[1] == NULL){
            swap(minheap[1],minheap[k]);
            k--;
            minheap.pop_back();
        }

        Min_Heapify(minheap,1); 
    }
    while(minheap[1] != NULL){
        ret.push_back(minheap[1]->val);
        minheap[1] = minheap[1]->next;
    }
    
    return ret;
}

int main()
{
    
    //arr为要排序的数组
	int arr[5][5] = {4, 9, 14, 19, 24,
                     1, 6, 11, 16, 21,
                     2, 7, 12, 17, 22,
                     3, 8, 13, 18, 23,
                     5, 10, 15, 20, 25};
    ListNode *l[5];
    for(int i = 0; i < 5; i++){
        l[i] = create_linklist(arr[i], sizeof(arr[i])/sizeof(int));
    }
    vector<int> v = k_merge(l,5);
    copy (v.begin(), v.end(), ostream_iterator<int> (cout, " "));
    cout << endl;
    
      
}