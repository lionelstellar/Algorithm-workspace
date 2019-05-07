#include<iostream>
#include<cmath>
using namespace std;

void QuickSort(int* arr, int p, int q)
{
	if(p >= q){
		return;
	}
	else{
		int pivot = arr[p];
        int little_end = p;
        for(int i = p+1; i <= q; i++){
            if(arr[i] < pivot){
                little_end++;
                swap(arr[i],arr[little_end]);
            }
        }

        swap(arr[p], arr[little_end]);
        QuickSort(arr, p, little_end - 1);
        QuickSort(arr, little_end + 1, q);
        
	}

}

int main()
{
	int arr[10] = {5,2,4,7,10,9,8,1,6,3};
	
	QuickSort(arr,0,9);

	for(int i = 0; i < 10; i++){
		cout << arr[i] <<' ';
		cout << endl;
	}

	
	
}