#include<iostream>
#include<cmath>
using namespace std;
/**
 * @brief 对向量v进行冒泡排序
 * @param v     待排序的向量
 */
void Merge(int* arr, int start, int end, int* result){
	int i,j = 0;
	int mid = (ceil(start + end)/2);
	int left_index = start;
	int right_index = mid + 1;
    int result_index = start;

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


void MergeSort(int* arr, int start, int end, int* result)
{
	if(0 == end - start){
		return;
	}
	else{
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
