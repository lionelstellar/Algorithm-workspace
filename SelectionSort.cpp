#include<iostream>
#include<vector>
using namespace std;

/**
 * @brief 对向量v进行选择排序
 * @param v     待排序的向量
 */
void SelectionSort(vector<int> &v)
{
	int min, min_index;

    //从第一个元素开始遍历数组
	for(int i = 0; i < v.size() - 1; i++){
        //初始化为首个元素及其下标
		min = v[i];
        min_index = i;

        //内循环后min和min_index保存未排序部分中的最小值及其下标
        for(int j = i + 1; j < v.size(); j++){
            if(v[j] < min){
                min = v[j];
                min_index = j;
            }
        }
        
        //找到最小值后，交换与当前值的位置
        swap(v[i], v[min_index]);
        
	}
}

int main()
{
	//arr为要排序的数组
	int arr[] = {5,2,4,7,10,9,8,1,6,3};

	//把数组放入向量中
	vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
	
	//对向量使用选择排序
	SelectionSort(v);

	//按顺序打印排序后向量中的所有元素
	copy (v.begin(), v.end(), ostream_iterator<int> (cout, " "));
    cout << endl;
	
}