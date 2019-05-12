#include<iostream>
#include<vector>
using namespace std;
/**
 * @brief 对向量v进行冒泡排序
 * @param v     待排序的向量
 */
void BubbleSort(vector<int> &v)
{
    for(int i = 0; i < v.size() - 1; i++)
        for(int j = v.size() - 1; j > i; j--)
            if(v[j-1] > v[j])
                swap(v[j-1], v[j]);
}

int main()
{
    //arr为要排序的数组
	int arr[] = {5,2,4,7,10,9,8,1,6,3};

	//把数组放入向量中
	vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
	
	//对向量使用插入排序
	BubbleSort(v);

	//按顺序打印排序后向量中的所有元素
	copy (v.begin(), v.end(), ostream_iterator<int> (cout, " "));
    cout << endl;
}