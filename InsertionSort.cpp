#include<iostream>
#include<vector>
using namespace std;
//对向量进行插入排序
void InsertionSort(vector<int> &v)
{
	int i, j, key;

    //从第二个元素开始遍历数组
	for(i = 1; i < v.size(); i++){

		//取要插入的元素key
		key = v[i];

		//倒过来遍历key左边的sorted list, 如果不插入则右移一位直到j停留的位置值小于key或来到头部
		j = i - 1;
		while(j >= 0 && v[j] > key){
			v[j+1] = v[j];
			j--;
		}
		
		//插入key
		v[j+1] = key;
	}
}

int main()
{
	//arr为要排序的数组
	int arr[] = {5,2,4,7,10,9,8,1,6,3};

	//把数组放入向量中
	vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
	
	//对向量使用插入排序
	InsertionSort(v);

	//按顺序打印排序后向量中的所有元素
	copy (v.begin(), v.end(), ostream_iterator<int> (cout, " "));
    cout << endl;
	
}