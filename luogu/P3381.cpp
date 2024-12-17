#include<bits/stdc++.h>
#define int long long
#define ll long long

using namespace std;

const int N = 207,M = 5007;	
const ll inf = LONG_LONG_MAX;


int n,m,str,ed;

struct EDGE{
	int to,nxt,val,wea;
}e[M<<1];

int qcnt = 1, h[N], cur[N];

void addedge(int x,int y,int z,int w)
{
	e[++qcnt] = (EDGE){y,h[x],z,w};
	h[x] = qcnt;
}

int lv[N];

bool bfs()
{
	//cerr<<"YES\n";
	memset(lv,0,sizeof(lv));
	memcpy(cur,h,sizeof(h));
	queue<int> q;
	q.push(str);
	lv[str] = 1;// 注意初值不能为0
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for(int i = h[u]; i; i = e[i].nxt)
		{
			int v = e[i].to;
			if(!lv[v] && e[i].val)
			{
				lv[v] = lv[u] + 1;
				q.push(v);
			}
		}
	}
	return lv[ed] != 0;
}

int dis[N],vis[N];

bool spfa()
{
	for(int i = 1;i <=n; ++i) lv[i] = 0,dis[i] = LONG_LONG_MAX;
	queue<int> q;
	dis[str] = 0;
	q.push(str), vis[str] = 1;
	while(!q.empty())
	{
		int u = q.front(); q.pop(); vis[u] = 0;
		for(int i = h[u]; i; i = e[i].nxt)
		{
			int v = e[i].to;
			if(dis[v] > dis[u] + e[i].wea)
			{
				dis[v] = dis[u] + e[i].wea;
				lv[v] = lv[u] + 1;
				if(!vis[v])
				{
					q.push(v); vis[v] = 1;
				}
			}
		}
	}
	return lv[ed] != 0;
}

ll dfs(int x,ll flow)
{
	if(x == ed) return flow;
	ll used = 0;
	for(int &i = cur[x]; i; i = e[i].nxt)
	{
		int v = e[i].to, w = e[i].val;
		if(lv[v] == lv[x] + 1 && w)
		{
			ll cst = dfs(v,min(flow - used,1ll*w));
			used += cst;
			e[i].val -= cst;
			e[i^1].val += cst;
			if(used == flow) return flow;
		}
	}
	return used;
}

ll dinic()
{

	ll res=0;
	while(bfs()) res += dis[ed] * dfs(str,inf);
	return res;
}

signed main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n>>m>>str>>ed;
	for(int i = 1; i <= m; ++i)
	{
		int u,v,w,x;
		cin>>u>>v>>w>>x;
		addedge(u,v,w,x), addedge(v,u,0,-x);
	}
	cout<<dinic();
	return 0;
}