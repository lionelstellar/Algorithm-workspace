#include<iostream>
#include<cmath>
using namespace std;

void QuickSort(int* arr, int start, int end)
{
	if(start >= end){
		return;
	}
	else{
		//startARTITION
		int pivot = arr[start];
        int little_end = start;
        for(int i = start+1; i <= end; i++){
            if(arr[i] < pivot){
                little_end++;
                swap(arr[i],arr[little_end]);
            }
        }

        swap(arr[start], arr[little_end]);

		//对子问题快排
        QuickSort(arr, start, little_end - 1);
        QuickSort(arr, little_end + 1, end);
        
	}

}

int main()
{
	int arr[10] = {5,2,4,7,10,9,8,1,6,3};
	
	QuickSort(arr,0,9);

	for(int i = 0; i < 10; i++){
		cout << arr[i] <<' ';
	}
	cout << endl;

	
	
}