#include<iostream>
#include<map>
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

int main()
{
    
    char ch[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {45, 13, 12, 16, 9, 5};
    
    
    
}