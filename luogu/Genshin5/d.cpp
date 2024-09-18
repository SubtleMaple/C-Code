#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

const int mod = 998244353;

int main()
{
    int n,ans=1;cin>>n;
    rep(i,1,n+1) ans = ans*i%mod;
    cout<<ans; 
    return 0;
}