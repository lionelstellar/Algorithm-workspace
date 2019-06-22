#include<iostream>
#include<vector>
using namespace std;
/**
 * @brief 贪心选择下次结束最早的活动加入result向量，增加活动a0，0时刻开始0时刻结束，便于运算
 * @param s         活动0~n的开始时间
 *        f         活动0~n的结束时间
 *        result    已被选择的活动编号
 */
void recursive_activity_selector(vector<int> s, vector<int> f, vector<int> &result)
{
    // 从i开始选择
    int i = result.back() + 1;
    
    while( i <= s.size() - 1 && s[i] < f[result.back()]){
        i++;
    }
    // 将合格的i加入result
    if(i <= s.size() - 1){
        result.push_back(i);
        recursive_activity_selector(s, f, result);
    }    
    // 结束时删掉活动a0
    else
        result.erase(result.begin());
}

/**
 * @brief 贪心选择下次结束最早的活动加入result向量，增加活动a0，0时刻开始0时刻结束，便于运算
 * @param s         活动0~n的开始时间
 *        f         活动0~n的结束时间
 *        result    已被选择的活动编号
 */
void greedy_activity_selector(vector<int> s, vector<int> f, vector<int> &result)
{
    int i = 1;
    // 将合格的i加入result
    while(i < s.size()){
        if(s[i] >= f[result.back()])
            result.push_back(i);
        i++;
    }

    // 结束时删掉活动a0
    result.erase(result.begin());
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
    vector<int> result1(1, 0);
    vector<int> result2(1, 0);
    // 递归贪心选择
    recursive_activity_selector(s, f, result1);

    // 迭代贪心选择
    greedy_activity_selector(s, f, result2);


    // 显示结果
    cout << "递归选择活动数：" << result1.size() << endl;
    cout << "递归选择活动编号：";
    copy (result1.begin(), result1.end(), ostream_iterator<int> (cout, " "));
    cout << endl;

    cout << "迭代选择活动数：" << result2.size() << endl;
    cout << "迭代选择活动编号：";
    copy (result2.begin(), result2.end(), ostream_iterator<int> (cout, " "));
    cout << endl;

    



}
