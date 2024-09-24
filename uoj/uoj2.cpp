#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
const int N = 1e5+3;
int n,m,t[N];
string op[N];

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    rep(i,1,n) cin>>op[i]>>t[i];
    int a0=0,a1=(~0);
    rep(i,1,n)
    {
        int o = op[i][0];
        if(o=='A'){
            a0 &= t[i], a1&=t[i];
        }
        else if(o=='O'){
            a0 |= t[i], a1 |= t[i];
        }
        else a0 ^= t[i], a1 ^= t[i];
    }
    int ans=0;
    for(int i=30;i>=0;i--)
    {
        int bit = 1<<i;
        if(a0&bit){
            ans += bit;
        }
        else if(a1&bit && m >= bit)
        {
            ans += bit; m -= bit;
        }
    }
    cout<<ans;

    return 0;
}