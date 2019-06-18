#include<iostream>
#include<vector>
using namespace std;
/**
 * @brief matrix chain order problem (bottom-up method)
 * @param p     the colume of A1~n, p0 is the row of A1
 * @param m     m[i,j] is the optimization of matrix multiply of Ai to Aj
 * @param s     s[i,j] is the break point of matrix chain Ai...j in the optimization
 * equation:    m[i,j] = min(m[i,k] + m[k+1,j] + Ai-1AkAj) (i<k<j)
 *              m[i,i] = 0
 */
void matrix_chain_order(vector<int> p, vector< vector<int> > &m, vector< vector<int> > &s)
{
    int temp;
    // i表示起始矩阵Ai;
    // gap表示Ai到Aj的距离, gap = j - i. 当gap值越大时, 可以用到小gap的子问题解.
    for(int gap=1; gap <= p.size()-2; gap++)
        for(int i = 1; i <= p.size() - gap - 1; i++){
            m[i][i + gap] = INT_MAX;
            for(int k = i; k < i + gap; k++){
                temp = m[i][k] + m[k+1][i+gap] + p[i-1]*p[k]*p[i + gap];
                if(m[i][i + gap] > temp){
                    m[i][i + gap] = temp;
                    s[i][i + gap] = k;
                } 
            }
        }
}
/**
 * @brief print the optimal partern to caculate the multiplication of matrix chain
 * @param s     s[i,j] is the break point of matrix chain Ai...j in the optimization
 */
void print_optimal_partern(vector< vector<int> > s, int i, int j){
    if(i == j)
        cout << "A" << i;
    else{
        cout << "(";
        print_optimal_partern(s,i,s[i][j]);
        print_optimal_partern(s,s[i][j] + 1,j);
        cout << ")";
    }
}

int main()
{
    int arr[] = {30, 35, 15, 5, 10, 20, 25};
    int len = sizeof(arr)/sizeof(int);
    vector<int> v(arr, arr + len);

    // 初始化二维向量m和s, 第0行和第0列无意义
    vector< vector<int> > m(len+1, vector<int>(len+1, 0));
    vector< vector<int> > s(len+1, vector<int>(len+1, 0));
    
    matrix_chain_order(v,m,s);

    // 打印m表
    cout << "m表：" << endl;
    for(int i = 1; i < len; i++){
        for(int j = i; j < len; j++)
            cout <<  m[i][j] << ",";
        cout << endl;
    }

    // 打印s表
    cout << "s表：" << endl;
    for(int i = 1; i < len; i++){
        for(int j = i + 1; j < len; j++)
            cout <<  s[i][j] << ",";
        cout << endl;
    }
    // 打印A1乘到A6的最优加括号方法   
    print_optimal_partern(s,1,6);
    
            
}