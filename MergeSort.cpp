#include<iostream>
#include<cmath>
using namespace std;
/**
 * @brief 对两个有序序列合并
 * @param arr    原数组
 * @param start  待合并的数组起始下标
 * @param end    待合并的数组结尾下标
 * @param result 合并后的数组
 */
void Merge(int* arr, int start, int end, int* result){
    
	int i,j = 0;
	int mid = (ceil(start + end)/2);
	int left_index = start;
	int right_index = mid + 1;
    int result_index = start;

	//左右都非空时，循环取左右中的最小元素尾插到result数组
	while( left_index < mid + 1 && right_index < end + 1){
		if(arr[left_index] <= arr[right_index]){
			result[result_index] = arr[left_index];
			left_index++;
		}
		else{
			result[result_index] = arr[right_index];
			right_index++;
		}
		result_index++;
	}

	//左右有一个为空，则将非空的数组元素放到result末尾
	while(left_index < mid + 1){
		result[result_index] = arr[left_index];
		result_index++;
		left_index++;
	}
	while(right_index < end + 1){
		result[result_index] = arr[right_index];
		result_index++;
		right_index++;
	}
}

/**
 * @brief 归并排序
 * @param arr    待排序的数组
 * @param start  待排序的数组起始下标
 * @param end    待排序的数组结尾下标
 * @param result 保存临时结果的数组
 */
void MergeSort(int* arr, int start, int end, int* result)
{
	//规模为0时不需进行任何操作
	if(0 == end - start){
		return;
	}
	else{

		//递归地对左右序列排序，合并到result中以后覆盖arr中的对应位置元素
		MergeSort(arr,start,ceil((start+end)/2), result);
		MergeSort(arr,ceil((start+end)/2)+1,end, result);
		Merge(arr,start,end,result);
		for(int i = start; i <= end; i++){
			arr[i] = result[i];
		}

	}

}
	


int main()
{
	int arr[10] = {5,2,4,7,10,9,8,1,6,3};
	int result[10];
	MergeSort(arr,0,9,result);

	for(int i = 0; i < 10; i++){
		cout << arr[i] <<' ';
	}
	
}
