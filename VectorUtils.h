#include<iostream>
#include<vector>
using namespace std;
template<class T>
void display(vector<T> v)
{
    copy (v.begin(), v.end(), ostream_iterator<T> (cout, " "));
    cout << endl;
}