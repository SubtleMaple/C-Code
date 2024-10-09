#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i)

const int N = 1e5+3;

struct EDGE{
    int to,nxt,l,w,nxtw;
}e[N<<1];

int h[N],qcnt,in[N];

int n,m,k,ans;

map<int,int> f[N];

int get_w(int w)
{
    if(k==1) return 1;
    int res = 1,ori_w=w;
    for(int i = 2; i * i <= ori_w; i++)
    {
        if(w%i) continue;
        int tot=0;
        while(w%i==0) w /= i,tot++;
        tot %= k;   
        if(tot==0) continue;
        rep(j,1,tot) res *= i;    
    }
    if(w != 1) res *= w;
    return res;
}

int get_nxtw(int w)
{
    if(k==1) return 1;  
    int res = 1,ori_w = w;
    for(int i = 2; i * i <= ori_w; ++i)
    {
        if(w%i) continue;
        int tot = 0;
        while(w % i == 0) w /= i, tot++;
        tot %= k;
        if(tot==0) continue;
        rep(j,1,k-tot) res *= i;
    }
    if(w != 1) rep(i,1,k-1) res *= w;
    return res;
}

void addedge(int x,int y,int z,int w)
{
    ++qcnt; int &i = qcnt;
    e[i].to = y;
    e[i].nxt = h[x];
    e[i].l = z;
   // ans = max(ans,z);
    e[i].w = get_w(w);
    e[i].nxtw = get_nxtw(w);
    h[x] = qcnt;
}

void solv()
{
    cin>>n>>m>>k;
    rep(i,1,m)
    {
        int u,v,w,l;
        cin>>u>>v>>w>>l;
        addedge(u,v,l,w), in[v]++;
    }

    queue<int> q;

    rep(i,1,n) if(!in[i]) q.push(i);

    while(!q.empty())
    {
        int u = q.front(); q.pop();

        for(int i=h[u];i;i=e[i].nxt)
        {
            int v = e[i].to;
            f[v][e[i].w] = max(f[v][e[i].w],f[u][e[i].nxtw]+e[i].l);
            ans = max(ans,f[v][e[i].w]);
            in[v]--;
            if(!in[v]) q.push(v);
        }
    }
    cout<<ans;
}

signed main()
{
    solv();
    return 0;
}