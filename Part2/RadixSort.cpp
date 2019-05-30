#include<iostream>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
using namespace std;
template<class T>
void display(vector<T> v){
    copy (v.begin(), v.end(), ostream_iterator<T> (cout, " "));
    cout << endl; 
}

int get_digit(int num, int d){
    return (num/(int)pow(10,d)) % 10;
}

//计数排序
void countingsort(vector<int> &v, vector<int> &v_str, int k)
{
    //初始化
    vector<int> temp(v.size(),0);
    vector<int> c(k + 1,0);
    
	
	
    //遍历一遍原数组，计数于c[k]中
    for(int i = 0; i < v.size(); i++)
    {
        c[v_str[i]] = c[v_str[i]] + 1;
    }
    //将c[k]中的计数累和
    for(int i = 1; i <= k + 1; i++)
    {
        c[i] = c[i] + c[i-1];
    }
	
    //将计数的元素存到temp中
    for(int j = v_str.size() - 1; j >= 0; j--)
    {
        temp[c[v_str[j]] - 1] = v[j];
        c[v_str[j]]--;
    }
    //把排序后的temp赋给v
    v = temp;
    display(v);
    

}


void radixsort(vector<int> &v, int d)
{
    vector<int> v_str;
    for( int j = 0; j < v.size(); j++)
        v_str.push_back(' ');
    

    for(int i = d - 1; i >= 0; i--){
        for( int j = 0; j < v.size(); j++)
        {
            v_str[j] = get_digit(v[j],d-1-i);
            
        }
        
        countingsort(v,v_str,9);
        
    }
}

int main()
{   
    
    int arr[] = { 329, 457, 657, 839, 436, 720, 355, 100, 492, 432, 845, 356};
    vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
    radixsort(v, 3);
    
    display(v);
   
}