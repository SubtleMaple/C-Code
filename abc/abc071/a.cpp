#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

int main()
{
    int a,b,c;cin>>a>>b>>c;
    cout << (abs(a-b) > abs(a-c) ? "B" : "A");
    return 0;
}