#include<iostream>
#include<vector>
using namespace std;

template<class T>
void display(vector<T> v){
    copy (v.begin(), v.end(), ostream_iterator<T> (cout, " "));
    cout << endl; 
}

/**
 * @brief 插入排序
 * @param v     待排序的向量
 */
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

/**
 * @brief 桶排序
 * @param v     待排序的向量
 */
void bucketsort(vector<int> &v)
{
    //num
    int num = 6;
    int step = 10;
    vector< vector<int> > bucket(num);
    vector<int> result;

    //放进不同的桶
    for(int i = 0; i < v.size(); i++){
        bucket[(int)(v[i]/step)].push_back(v[i]); 
    }
   
    //对每个桶中的元素进行排序
    for(int i = 0; i < num; i++){
        InsertionSort(bucket[i]);
        display(bucket[i]);
        result.insert(result.end(),bucket[i].begin(),bucket[i].end());  
    }
    v = result;
}
 


int main()
{
    int arr[] = {29, 25, 3, 49, 9, 37, 21, 43};
    vector<int> v(arr, arr+sizeof(arr)/sizeof(int));
    
    bucketsort(v);
    

    display(v);
    
}