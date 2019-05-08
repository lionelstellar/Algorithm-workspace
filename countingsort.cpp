#include<iostream>
#include<vector>
using namespace std;
//计数排序
void countingsort(vector<int> &v, int k)
{
    //初始化
    vector<int> temp(v.size(),0);
    vector<int> c(k + 1,0);

	
	
    //遍历一遍原数组，计数与c[k]中
    for(int i = 0; i < v.size(); i++)
    {
        c[v[i]] = c[v[i]] + 1;
    }
    //将c[k]中的计数累和
    for(int i = 1; i <= k + 1; i++)
    {
        c[i] = c[i] + c[i-1];
    }
	
    //将计数的元素存到temp中
    for(int j = v.size() - 1; j >= 0; j--)
    {
        temp[c[v[j]] - 1] = v[j];
        c[v[j]]--;
    }
    //把排序后的temp赋给v
    v = temp;

}

int main()
{
    int arr[] = { 1, 2, 6, 4, 3, 5, 2, 6, 3, 4, 5 ,6};
    vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
    int k = 6;

    countingsort(v, k);

	copy (v.begin(), v.end(), ostream_iterator<int> (cout, " "));
    cout << endl; 
}