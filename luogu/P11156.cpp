#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

int main()
{
    int T;cin>>T;
    while(T--)
    {
        int n,a;
        cin>>n>>a;
        if(n%2) cout<<a<<' '<<1<<'\n';
        else cout<<1<<' '<<a<<'\n';
    }
    return 0;
}