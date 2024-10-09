#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
int main()
{
    int w,h,x,y,r;  
    cin>>w>>h>>x>>y>>r;

    if(r<x || w-x<r || r<y || h-y<r) cout<<"No\n";
    else cout<<"Yes\n";

    return 0;
}