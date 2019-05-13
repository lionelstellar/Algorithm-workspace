#include<iostream>
#include<vector>
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
    int random = GenRandom(start, end);
    swap(v[start], v[random]);

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
 * @brief   对v[start, end]区间进行随机化快速排序
 */
void RandomizedQuickSort(vector<int> &v, int start, int end){

    //随机划分后，再对主元左右两侧的序列进行快排
    if(start < end){
        int SplitIndex = RandomizedPartition(v, start, end);
        RandomizedQuickSort(v, start, SplitIndex-1);
        RandomizedQuickSort(v, SplitIndex + 1, end);
    }

}

int main()
{
    //arr为要排序的数组
	int arr[] = {5,2,4,7,10,9,8,1,6,3};

	//把数组放入向量中
	vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
	
	//对向量使用插入排序
	RandomizedQuickSort(v, 0, sizeof(arr)/sizeof(int)-1);

	//按顺序打印排序后向量中的所有元素
	copy (v.begin(), v.end(), ostream_iterator<int> (cout, " "));
    cout << endl;
	
}