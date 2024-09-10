#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;

const int N = 1e5+7, mod = 10007;

int n,m,c[N],num[N],ins[N][2],is[N][2],ns[N][2],cnt[N][2];

void md(int &x){
     x%=mod;
}

int main()
{
    freopen("data.in","r",stdin);
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    rep(i,1,n) cin>>num[i];
    rep(i,1,n) cin>>c[i];
    rep(i,1,n)
    {
        cnt[c[i]][i%2]++;
        md(ins[c[i]][i%2] += 1ll*i*num[i]%mod);
        md(ns[c[i]][i%2] += num[i]);
        md(is[c[i]][i%2] += i);
    }

    int ans=0;
    rep(i,1,m) rep(o,0,1)
    {
        md(ans += 1ll*ins[i][o]*(cnt[i][o]-2)%mod);
        md(ans += 1ll*is[i][o]*ns[i][o]%mod);
    }
    cout<<ans;

    return 0;
}