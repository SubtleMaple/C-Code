#include<bits/stdc++.h>
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;

const int M = 2e5+7;
const int N = 1e5+7;

int n,m,s,dis[N],vis[N];

struct EDGE{
    int to,nxt,val;
}e[M<<1];

int h[N],qcnt;

void addedge(int x,int y,int z)
{
    e[++qcnt] = (EDGE){y,h[x],z};
    h[x] = qcnt;
}

struct Node
{
    int id,val;
    friend bool operator<(Node a,Node b)
    {
        return a.val > b.val;
    }
};
priority_queue<Node> q;

void dijkstra()
{
    q.push((Node){s,dis[s]});
    while(!q.empty())
    {
        Node now = q.top(); q.pop();
        int u = now.id;
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = h[u];i;i=e[i].nxt)
        {
            int v = e[i].to;
            if(dis[v] > dis[u]+e[i].val)
            {
                dis[v] = dis[u]+e[i].val;
                if(!vis[v]) q.push((Node){v,dis[v]});
            }
        }
    }
}

queue<int> qu;

void spfa()
{
    dis[s] = 0;
    qu.push(s),vis[s] = 1;
    while(!qu.empty())
    {
        int u = qu.front(); qu.pop(); vis[u] = 0;
        for(int i = h[u];i;i=e[i].nxt)
        {
            int v = e[i].to;
            if(dis[v] > dis[u] + e[i].val)
            {
                dis[v] = dis[u] + e[i].val;
                if(!vis[v]) qu.push(v); vis[v] = 1;
            }
        }


    }


}

signed main()
{
    //freopen("data.in","r",stdin);
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>s;
    rep(i,1,n) dis[i] = 2147483647;
    dis[s] = 0;
    rep(i,1,m)
    {
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
    }
    //dijkstra();
    spfa();
    rep(i,1,n) cout<<dis[i]<<' ';


    return 0;
}