#include<iostream>
using namespace std;

void myswap(int &a, int &b)
{
    cout << "Before：" << endl;
    cout << &a << ' ' << &b << endl;
    cout << a << ' ' << b << endl;
    int temp = *&a;
    *&a = *&b;
    *&b = temp;
    cout << "After：" << endl;
    cout << &a << ' ' << &b << endl;
    cout << a << ' ' << b << endl;

}

int main(){
    int a = 3,b = 4;

    myswap(a,b);
    cout << &a << ' ' << &b << endl;
    cout << a << ' ' << b << endl;
}