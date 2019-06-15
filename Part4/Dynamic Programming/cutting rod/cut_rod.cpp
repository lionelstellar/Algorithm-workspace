/**
 * @brief cut rod problem
 * price table
 * length i  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
 * price  p  |  1  |  5  |  8  |  9  |  10 |  17 |  17 |  20 |  24 |  30  |
 * 
 * How can we make most of the rod of length L, return the most we can sell.
 * 
 */
#include<iostream>
#include<vector>
using namespace std;
static int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
static int max_len = 10;

/**
 * method 1:
 * @brief cut rod problem (top-down method)
 * @param n  the length of rod we have
 */
int cut_rod(int n)
{
    if(n == 0)
        return 0;
    int j = 0;
    int q = INT_MIN;
    for(j = 1; j <= n; j++){
        if(j <= max_len)
            q = max(q, p[j] + cut_rod(n-j));
        
    }
    return q;
}

/**
 * method 2:
 * @brief cut rod problem (top-down with memorization)
 * @param n  the length of rod we have
 */
int memoized_cut_rod_aux(int n, vector<int> &v)
{
    if(v[n] >= 0)
        return v[n];
    int q;
    if(n == 0)
        q = 0;
    else{
        q = INT_MIN;
        for(int i = 1; i <= n; i++){
            if(i <= max_len)
                q = max(q, p[i] + memoized_cut_rod_aux(n-i,v));
        }       
    }
    v[n] = q;
    return q;
}

int memorized_cut_rod(int n)
{
    // 向量v存储子问题的最优解
    vector<int> v(n+1,INT_MIN);
    
    return memoized_cut_rod_aux(n,v);
    
}
 


/**
 * method 3:
 * @brief cut rod problem (bottom_up method)
 * @param n  the length of rod we have
 */
int bottom_up_cut_rod(int n)
{
    int i,j = 0;
    int q;
    // 向量v存储子问题的最优解
    vector<int> v(n+1, 0);
    
    for(j = 1; j <= n; j++){
        q = INT_MIN;
        for(i = 0; i <= j; i++){
            // 动态转移方程
            if(i <= max_len)
                q = max(q, p[i] + v[j-i]);
        }
        v[j] = q;
        
    }
    return v[n];
}

int main()
{
    //enumeration programming
    cout << "自顶向下法切长度为10：" << cut_rod(10) << endl;

    //dynamic programming
    cout << "带备忘录自顶向下法切长度为8：" << memorized_cut_rod(8) << endl;
    cout << "自底向上法切长度为9：" << bottom_up_cut_rod(9) << endl;

}