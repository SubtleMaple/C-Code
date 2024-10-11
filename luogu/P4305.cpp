#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i)

const int mod = 1000003;

vector<int> h[mod];

int hsh(int x){
    return (x%mod+mod)%mod;
}


void solv()
{
    int n; cin>>n;
    rep(i,1,n)
    {
        int x; cin>>x;
        bool flg=0;
        for(int j=0;j<(int)h[hsh(x)].size();++j)
            flg |= (x==h[hsh(x)][j]);
        if(flg) continue;
        h[hsh(x)].push_back(x);
        cout<<x<<' ';
    }   
    cout<<'\n';
    rep(i,0,mod-1) h[i].clear();
}

signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int tt;cin>>tt;
    while(tt--) solv();
    return 0;
}