#include<iostream>

using namespace std;

int main()
{
	int a = 10, b = 10;
	const int *p = &a;//常量指针：指向可以修改，指向的值不可改 
	*p = 20;//不可，因为 p 指向的 a被改了
	p = &b;//可，因为p指向可以改
	int *const p = &a; // 指针常量：指向不可改，指向的值可改
	const int *const p = &a; //指针的指向与指向的值都不可改
	
	return 0;
}
