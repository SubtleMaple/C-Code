#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

int main()
{   
    int *a = new int [10];//开辟内存空间，并将首地址作为返回值
    rep(i,0,9) *(a+i)=i;
    for(int *p = a+9;p>=a;p--) cout<<*p<<' ';
    cout<<'\n';
    delete []a;

    return 0;
}