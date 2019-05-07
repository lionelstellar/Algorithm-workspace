#include<iostream>
#include<vector>
#include"VectorUtils.h"
using namespace std;

//返回最大值max，改变起始下标left与结束下标right
int find(vector<int> &v, int &left, int &right)
{
    int i = 0;
    int max = INT_MIN;
    int sum = 0;
    int begin = 0;
    //动态转移：DP[i + 1] = max{DP[i] + A[i] , A[i]}, 循环一次可解决问题
    for(i = 0; i < v.size(); i++){
        //DP[i + 1] = DP[i] + A[i]
        if(sum > 0){
            sum += v[i];
        }
        //DP[i + 1] = A[i]
        else{
            sum = v[i];
            begin = i;
        }
        //当前和sum比记录的max大，更新起止下标及max的值
        if(sum > max){
            max = sum;
            left = begin;
            right = i;
        }

    }
    
    return max;
}



int main()
{   int left = 0;
    int right = 0;
    int arr[] = {2,4,-7,5,2,-1,2,-4,3};
    vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
   
    
    
    cout << "max:" << find(v,left,right) << endl;
    cout << left << " " << right << endl;
}