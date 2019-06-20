#include<iostream>
#include<vector>
using namespace std;

void recursive_activity_selector(vector<int> s, vector<int> f, vector<int> &result)
{

    int i = result.back() + 1;
    
    while( i <= s.size() - 1 && s[i] < f[result.back()]){
        i++;
    }
    if(i <= s.size() - 1){
        result.push_back(i);
        recursive_activity_selector(s, f, result);
    }    
}

int main()
{
    // 添加活动a0, 起始终止时刻均为0.
    // 开始时间
    int start[] = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    // 结束时间(sorted)
    int finish[] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    vector<int> s(start, start + sizeof(start)/sizeof(int));
    vector<int> f(finish, finish + sizeof(finish)/sizeof(int));

    // 选择结果
    vector<int> result(1, 0);
    recursive_activity_selector(s, f, result);
    cout << "选择活动数：" << result.size() - 1 << endl;
    cout << "选择活动编号：";
    copy (result.begin() + 1, result.end(), ostream_iterator<int> (cout, " "));
    cout << endl;


    

}
