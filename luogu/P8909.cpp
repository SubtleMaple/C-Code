#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

unordered_map<int,int> f;

int n,m,ans[2507];

int main()
{
    
    cin>>n>>m;
    rep(i,1,n)
    {
        int x; cin>>x;
        for(int j=x;j<=m;j+=x) f[j]++;
    }
    for(auto it = f.begin();it!=f.end();it++)
    {
        ans[it->second]++; m--;
    }
    cout<<m<<' ';
    rep(i,1,n) cout<<ans[i]<<' ';
    return 0;
}