#include<iostream>
#define lb(i) (i&-i)

using namespace std;


signed main()
{
	int a=1,b=2;
	b = a^b;
	a = a^b;
	b = a^b;
	cout<<a<<' '<<b;
	
	return 0;
}
