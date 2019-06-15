/**
 * @brief cut rod problem
 * price table
 * length i  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
 * price  p  |  1  |  5  |  8  |  9  |  10 |  17 |  17 |  20 |  24 |  30  |
 * 
 * How can we make most of the rod of length L, return the most we can sell and how we should cut.
 * 
 */
#include<iostream>
#include<vector>
using namespace std;
static int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
static int max_len = 10;

/**
 * @brief cut rod problem (top-down with memorization)
 * @param n  the length of rod we have
 */
int extend_memoized_cut_rod_aux(int n, vector<int> &v, vector< vector<int> > &solution)
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
                if(q < p[i] + extend_memoized_cut_rod_aux(n-i,v,solution)){
                    q = p[i] + extend_memoized_cut_rod_aux(n-i,v,solution);
                    solution[n].clear(); 
                    solution[n].insert(solution[n].end(), solution[n-i].begin(), solution[n-i].end());
                    solution[n].push_back(i);
                }
                
                
        }       
    }
    v[n] = q;
    return q;
}

int extend_memorized_cut_rod(int n)
{
    vector<int> v(n+1,INT_MIN);
    //额外空间存储切分方式
    vector< vector<int> > solution(n+1, vector<int>(0));
    
    
    int best_price = extend_memoized_cut_rod_aux(n,v,solution);


    copy (solution[n].begin(), solution[n].end(), ostream_iterator<int> (cout, " "));
    cout << endl;
    return best_price;
    
}
 


/**
 * @brief cut rod problem (bottom_up method)
 * @param n  the length of rod we have
 */
int bottom_up_cut_rod(int n)
{
    int i,j = 0;
    int q;
    vector<int> v(n+1, 0);
    //额外空间存储切分方式
    vector< vector<int> > solution(n+1, vector<int>(0));
    
    for(j = 1; j <= n; j++){
        q = INT_MIN;
        for(i = 0; i <= j; i++){
            if(i <= max_len)
                if(q < p[i] + v[j-i]){
                    q = p[i] + v[j-i];
                    solution[j].clear();
                    solution[j].insert(solution[j].end(), solution[j-i].begin(), solution[j-i].end());
                    solution[j].push_back(i);
                }
                
        }
        v[j] = q;
        
    }
    copy (solution[n].begin(), solution[n].end(), ostream_iterator<int> (cout, " "));
    cout << endl;
    return v[n];
}

int main()
{
    
    /* 
    for(int i = 0; i < 11; i ++){
        cout << "带备忘录自顶向下法切长度为" << i << "：" << extend_memorized_cut_rod(i) << endl;
    }
    */
    
    
    for(int i = 0; i < 11; i ++){
        cout << "自底向上法切长度为" << i << "：" << bottom_up_cut_rod(i) << endl;
    }

}