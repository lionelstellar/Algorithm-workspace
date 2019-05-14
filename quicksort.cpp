#include<iostream>
#include<cmath>
using namespace std;
/**
 * @brief   对arr[start, end]区间进行随机化快速排序
 * @param arr     待排序的数组
 * @param start   序列的开始下标
 * @param end     序列的终止下标
 */
void QuickSort(int* arr, int start, int end)
{	
	//起始下标不小于终止下标，就不需要再分区
	if(start >= end){
		return;
	}
	else{
		//开始分区
		int pivot = arr[start];
        int little_end = start;
        for(int i = start+1; i <= end; i++){
            if(arr[i] < pivot){
                little_end++;
                swap(arr[i],arr[little_end]);
            }
        }

        swap(arr[start], arr[little_end]);

		//分区完成后对子问题快排
        QuickSort(arr, start, little_end - 1);
        QuickSort(arr, little_end + 1, end);
        
	}

}

int main()
{
	int arr[] = {5,2,4,7,10,9,8,1,6,3};
	
	QuickSort(arr,0,sizeof(arr)/sizeof(int) - 1);

	for(int i = 0; i < sizeof(arr)/sizeof(int); i++){
		cout << arr[i] <<' ';
	}
	cout << endl;	
}