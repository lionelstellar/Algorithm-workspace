#include<iostream>
#include<vector>
using namespace std;

void bubblesort(vector<int> &v)
{
    for(int i = 0; i < v.size(); i++)
        for(int j = v.size() - 1; j > i; j--)
            if(v[j-1] > v[j])
                swap(v[j-1], v[j]);
}

int main()
{
    int arr[] = {5,2,4,7,10,9,8,1,6,3};
    vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
    
    bubblesort(v);

    copy (v.begin(), v.end(), ostream_iterator<int> (cout, " "));
    cout << endl;
}