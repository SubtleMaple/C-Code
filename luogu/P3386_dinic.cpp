// dinic version
// point = 1 + 1 + n + m
// num_edge = (n + m + e)<<1
#include<bits/stdc++.h>

using namespace std;

const int N = 500, M = 500,E = 5000;
const int inf = INT_MAX;

struct EDGE{
	int to,nxt,val;
}e[(N+M+E)*2+7];

int h[N+M+3],cur[N+M+3],qcnt=1;

int n,m,ecnt;
int str,ed;

void addedge(int x,int y,int z)
{
	e[++qcnt] = (EDGE){y,h[x],z};
	h[x] = qcnt;
}

int lv[N+M+3];

bool bfs(int str)
{
	memset(lv,0,sizeof(lv));
	memcpy(cur,h,sizeof(h));
	queue<int> q;
	q.push(str);
	lv[str] = 1;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for(int i = h[u]; i; i = e[i].nxt)
		{
			int v = e[i].to;
			if(!lv[v] && e[i].val) {
				lv[v] = lv[u] + 1;
				q.push(v);
			}
		}
	}
	return lv[ed] != 0;
}

int dfs(int x,int flow)
{
	if(x == ed) return flow; // 递归终止条件：流向超级汇点
	int used = 0;
	for(int &i = cur[x]; i; i = e[i].nxt)
	{
		int v = e[i].to, w = e[i].val;
		if(lv[v] == lv[x] + 1 && w)
		{
			int cst = dfs(v,min(flow - used, w));
			used += cst;
			e[i].val -= cst;
			e[i^1].val += cst;
			if(used == flow) return flow;
		}
	}
	return used;
}

int dinic()
{
	int res=0;
	while(bfs(str))
	{
		//cerr<<"YES\n";
		res += dfs(str,inf);
	}
	return res;
}


int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n>>m>>ecnt;
	str = 0, ed = n + m + 1;
	for(int i = 1; i <= n; ++i) addedge(str,i,1),addedge(i,str,0);
	for(int i = 1; i <= m; ++i) addedge(i+n,ed,1),addedge(ed,i+n,0);
	for(int i = 1; i <= ecnt; ++i)
	{
		int u,v; cin >> u >> v;
		addedge(u,v+n,1);
		addedge(v+n,u,0);
	}
	cout<<dinic();
	return 0;
}