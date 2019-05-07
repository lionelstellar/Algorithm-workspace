#include<iostream>
#include<vector>
#include"VectorUtils.h"
using namespace std;
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
//维护最大堆的性质
void Max_Heapify(vector<int> &v, int i)
{
    int size = v.size() - 1;   
    int large;
    int l = left(i);
    int r = right(i);
    //左子大于父节点,large = l
    if(l <= size && v[l] > v[i])    large = l;
    else                            large = i;
    
    //large取右子和左子、父中的较大值节点
    if(r <= size && v[r] > v[large]){
        large = r;
    }

    if(large != i){
        swap(v[i],v[large]);
        Max_Heapify(v,large);
    }
}

//从最大parent节点往上维护最大堆性质，就能形成最大堆
void Build_Max_Heap(vector<int> &v)
{   
    //最后一个子节点v.size()/2向下取整是号码最大的parent节点，所以直接从这里count down
    for(int i = v.size()/2; i > 0; i--)
    {
        Max_Heapify(v,i);
    }
}
//堆排序
void Heapsort(vector<int> &v)
{
    vector<int> ret;
    
    Build_Max_Heap(v);
    //display(v);
    for(int i = v.size()-1; i > 1; i--)
    {
        swap(v[i], v[1]);
        ret.push_back(v[i]);
        v.pop_back();
        Max_Heapify(v,1);
        
        //display(v);
        
    }
    ret.push_back(v[1]);
    //display(ret);
    v = ret;
}



int main()
{
    int arr[] = {5,2,4,7,10,9,8,1,6,3};
	//int arr[] = {4,1,3,2,16,9,10,14,8,7};
    vector<int> v(arr, arr + sizeof(arr)/sizeof(int));

	//模拟堆的数组，第一个元素0是为了占一个位置，不属于堆
	v.insert(v.begin(),0);
    

    //Build_Max_Heap(v);
    //流迭代器打印vector
    Heapsort(v);
    display(v);
    
    
    
    

}