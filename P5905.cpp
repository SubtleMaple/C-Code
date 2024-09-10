#include<bits/stdc++.h>
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;

const int N = 3007, M = 6007;

struct EDGE{
    int to,nxt,val;
}e[M+N+7];

int h[N],qcnt;

void addedge(int x,int y,int z)
{
    e[++qcnt] = (EDGE){y,h[x],z};
    h[x] = qcnt;
}

int n,m,dis[N][N],ht[N],tim[N];
bool vis[N];
queue<int> qu;
bool spfa(int s)
{
    memset(ht,0x3f,sizeof(h));
    ht[s] = 0; qu.push(s); vis[s] = 1;
    while(!qu.empty())
    {
        int u = qu.front();qu.pop();vis[u] = 0;
        for(int i=h[u];i;i=e[i].nxt)
        {
            int v = e[i].to;
            if(ht[v] > ht[u]+e[i].val)
            {
                ht[v] = ht[u]+e[i].val;
                if(!vis[v]){
                    qu.push(v); vis[v] = 1;
                    tim[v]++;
                    if(tim[v]>n) return 0; //判负环
                }
            }
        }
    }
    return 1;
}

struct Node{
    int id,val;
    friend bool operator<(Node a,Node b){
        return a.val > b.val;
    }
};

priority_queue<Node> q;

void dij(int s)
{
    rep(i,1,n) dis[s][i] = 1000000000;  
    rep(i,1,n) vis[i] = 0;
    dis[s][s] = 0; q.push((Node){s,dis[s][s]}); 
    while(!q.empty())
    {
        Node now = q.top(); q.pop();
        int u = now.id;
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i=h[u];i;i=e[i].nxt)
        {
            int v = e[i].to;
            if(dis[s][v] > dis[s][u] + e[i].val)
            {
                dis[s][v] = dis[s][u] + e[i].val;
                if(!vis[v]) q.push((Node){v,dis[s][v]});
            }
        }
    }

}



signed main()
{
    freopen("data.in","r",stdin);
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    rep(i,1,m)
    {
        int x,y,z;cin>>x>>y>>z;
        addedge(x,y,z);
    }
    rep(i,1,n) addedge(n+1,i,0);

    if(!spfa(n+1)) {
        cout<<-1;return 0;
    }
    rep(u,1,n)
      for(int i=h[u];i;i=e[i].nxt)
      {
        int v = e[i].to;
        e[i].val = e[i].val + ht[u] - ht[v];
      }

    rep(i,1,n) 
    {
        dij(i);
    }
    long long ans = 0ll;
    rep(i,1,n)
    {
        ans = 0ll;
        rep(j,1,n) // 注意单独判断不联通情况
        {
            if(dis[i][j] == 1000000000) ans += 1ll*dis[i][j]*j;
            else ans += 1ll*(dis[i][j] - ht[i] + ht[j])*j;
        }
        cout<<ans<<'\n';
    }
    

    return 0;
}