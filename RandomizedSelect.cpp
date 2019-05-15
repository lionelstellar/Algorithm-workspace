#include<iostream>
#include<vector>
#include"VectorUtils.h"
using namespace std;
/**
 * @brief 生成[start, end]区间内的随机整数
 */
int GenRandom(int start, int end){
    srand((unsigned)time(NULL));
    return rand()%(end - start + 1) + start;
}

/**
 * @brief   对v[start, end]区间进行随机划分
 * @return  主元的索引
 */
int RandomizedPartition(vector<int> &v, int start, int end){
    //生成一个区间内随机数，将该位置元素与第一位元素交换
    //int random = GenRandom(start, end);
    //swap(v[start], v[random]);

    //将之前随机选出的值作为主元，小于主元的元素置于左边，否则置于右边，最后返回主元的下标
    int pivot = v[start];
    int little_end = start;
    for(int i = start + 1; i <= end; i++){
        if(v[i] < pivot){
            little_end++;
            swap(v[little_end], v[i]);
        }
    }
    swap(v[start], v[little_end]);
    
    return little_end;
    
}

/**
 * @brief   对v[start, end]随机选择第i小的元素
 * @return  主元的索引
 */
int RandomizedSelect(vector<int> &v, int start, int end, int i){
    
    if(start == end){
        return v[start];
    }
    
    int q = RandomizedPartition(v, start, end);
    
    int k = q - start + 1;
    //恰好找到，返回pivot
    if(k == i){
        return v[q];
    }
    else if(k < i){
        return RandomizedSelect(v, q + 1, end, i - k); 
    }
    else{
        return RandomizedSelect(v, start, q - 1, i);
    }

}

int main()
{
    int arr[] = {5,2,4,7,10,9,8,1,6,3};
    
    vector<int> v(arr, arr+sizeof(arr)/sizeof(int));

    int index = 8;
    int result = RandomizedSelect(v, 0, v.size() - 1, index);

    cout << "数组中第" << index << "大的数是" << result <<endl;
}