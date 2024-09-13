#include<iostream>

using namespace std;

int main()
{
	int a = 10,b = 5;
    int *p = &a;
    cout<<*p<<'\n';
    int * &q = p; // 引用了一个指针
    q = &b;
    cout<<*p<<'\n';
	
	return 0;
}
