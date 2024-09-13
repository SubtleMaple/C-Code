#include<iostream>

using namespace std;


void swap01(int a,int b)
{
	int t = a; a = b, b = t;
}

void swap02(int *a,int *b)
{
	int t = *a; *a = *b, *b = t;//一个地址对应一个变量，将地址传入函数则直接对
				    //地址上的变量进行修改
}

int main()
{
	int a = 5, b = 10;
	swap01(a,b);
	cout<<a<<' '<<b<<'\n';
	swap02(&a,&b);
	cout<<a<<' '<<b<<'\n';


	return 0;
}

