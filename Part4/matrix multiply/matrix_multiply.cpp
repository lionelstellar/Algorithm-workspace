#include<iostream>
#include<vector>
using namespace std;
/**
 * method 1:
 * @brief matrix chain order problem (bottom-up method)
 * @param p     the colume of A1~n, p0 is the row of A1
 * @param m     m[i,j] is the optimization of matrix multiply of Ai to Aj
 * @param s     s[i,j] is the break point of matrix chain Ai...j in the optimization
 */
void matrix_chain_order(vector<int> p, int** &m, int** &s)
{

}

int main()
{
    int arr[] = {30, 35, 15, 5, 10, 20, 25};
    int len = sizeof(arr)/sizeof(int);
    vector<int> v(arr, arr + len);

    int **m;
    m = (int **)malloc(len*len*sizeof(int));



}