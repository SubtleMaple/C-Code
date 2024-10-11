#include<bits/stdc++.h>
#define int long long
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

const int mod1 = 212370440130137957ll;
const int mod2 = 99593441;

class HASH
{
    public:
    int mod,bit;
    int get_hash(string s)
    {
        int res=0;
        for(int i=0;s[i];i++)
        {
            res = (1ll*res*bit+s[i])%mod;
        }
        return res;
    }
}h1,h2;

int n;

pair<int,int> a[10003];

bool cmp(pair<int,int> x,pair<int,int> y)
{
    return x.first < y.first;
}


signed main()
{
    cin>>n;
    h1.mod = mod1,h2.mod = mod2;
    h1.bit = 131,h2.bit = 13331;
    rep(i,1,n)
    {
        string s; cin>>s;
        a[i] = {h1.get_hash(s),h2.get_hash(s)};
    }
    sort(a+1,a+n+1,cmp);
    int ans=0;
    rep(i,1,n) if(a[i].first!=a[i-1].first || a[i].second!=a[i-1].second)
        ans++;
    cout<<ans;

    return 0;
}