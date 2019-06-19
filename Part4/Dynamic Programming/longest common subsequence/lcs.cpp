#include<iostream>
#include<vector>
using namespace std;

int lcs_length(string X, string Y, vector< vector<int> > &c, vector< vector<string> > &b)
{
    int m = X.length();
    int n = Y.length();
    for(int i = 0; i <= m; i++)
        c[i][0] = 0;
    for(int j = 0; j <= m; j++)
        c[0][j] = 0;

    // bottom-up求解
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
        {
            if(X[i] == Y[j]){
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = "↖";
            }
            else if(c[i-1][j] > c[i][j-1]){
                c[i][j] = c[i-1][j];
                b[i][j] = "←";
            }
            else{
                c[i][j] = c[i][j-1];
                b[i][j] = "↑";
            }
        }
    return c[m][n];
}

void print_lcs(vector< vector<string> > b, string X, int i, int j)
{
    if(i == 0 or j == 0)
        return;
    if(b[i][j] == "↖"){
         cout << X.at(i-1);
         print_lcs(b, X, i-1, j-1);
    }  
    else if(b[i][j] == "↑"){
        print_lcs(b, X, i, j-1);
    }
    else{
        print_lcs(b, X, i-1, j);
    }
}

int main()
{
    string X = "ABCBDAB";
    string Y = "BDCABA";
    int m = X.length();
    int n = Y.length();
    // m+1行n+1列的表记录最大长度
    vector< vector<int> > c(m+1, vector<int>(n+1));
    // m+1行n+1列的表记录箭头
    vector< vector<string> > b(m+1, vector<string>(n+1));
    

    // lcs长度
    cout << "最大公共子序列长度为：" << lcs_length(X,Y,c,b) << endl;

    // 打印lcs
    cout << "最大公共子序列为：";
    print_lcs(b, X, m, n);
    












    

}