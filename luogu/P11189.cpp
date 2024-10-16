#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define ll long long

const int N = 100003;
const ll inf = 10000000000000LL;

ll a[N],d[N];

int n,fa[N];

struct EDGE{
    int to,nxt;
}e[N];

int qcnt,h[N];

void addedge(int x,int y){
    e[++qcnt] = (EDGE){y,h[x]}; h[x] = qcnt;
}

void print(bool x)
{
    if(x) cout<<"Huoyu\n";
    else cout<<"Shuiniao\n";
}

ll f[N]; // dp

bool chek(int x,ll s)
{
    ll sum = 0;
    // for(int i=h[x];i;i=e[i].nxt) sum += f[e[i].to];
    // if(sum < s) return 0;
    // sum = 0;
    for(int i=h[x];i;i=e[i].nxt)
    {
        int v = e[i].to;
        ll bv = max(0ll,s-abs(d[v]));
        if(bv > f[v]) return 0;
        sum += bv;
    }
    if(sum > s) return 0;
    return 1;
}

void dfs(int x)
{
    if(!h[x]){
        return; // 
    }
    ll uplim = 0;
    for(int i=h[x];i;i=e[i].nxt)
    {
        dfs(e[i].to);
        uplim += f[e[i].to];
    }
    //  s <= uplim
    ll l=0,r=uplim+1; // [l,r)
    while(l<r-1)
    {
        ll mid = l+r>>1;
        if(chek(x,mid)) l = mid;
        else r = mid;
        
    }
    f[x] = l;
}

void solv()
{
    cin>>n;

    qcnt = 0;
    rep(i,1,n) h[i] = 0,f[i] = inf;


    rep(i,2,n) 
    {
        cin>>fa[i];
        addedge(fa[i],i);
    }

    rep(i,1,n) cin>>a[i];
    rep(i,2,n) 
    {
        d[i] = a[i] - a[fa[i]];
        if(d[i] > 0) {
            print(0); return;
        }
    }
    dfs(1);
    f[1] >= a[1] ? print(1) : print(0);
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin>>tt; cin>>tt;
    while(tt--) solv();
    return 0;
}