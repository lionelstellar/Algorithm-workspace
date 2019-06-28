#include<iostream>
#include<vector>
using namespace std;

class HuffmanTreeNode{
    public:
        char key;
        double weight;
        HuffmanTreeNode *parent;
        HuffmanTreeNode *left;
        HuffmanTreeNode *right;
        HuffmanTreeNode(char k, double w, HuffmanTreeNode *p, HuffmanTreeNode *l, HuffmanTreeNode *r):
        key(k), weight(w), parent(p), left(l), right(r){}
};
// 找到最小的值的下标
int extract_min(vector<int> v)
{
    int min = INT_MAX;
    int flag = 0;
    for(int i = 0; i < v.size(); i++){
        if(v[i] < min){
            flag = i;
            min = v[i];
        }
    }

    return flag;
}

int main()
{
    
    char ch[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {45, 13, 12, 16, 9, 5};
    vector<int> freq_vec(ch, ch + sizeof(ch) / sizeof(int));

    
    
    
    
}