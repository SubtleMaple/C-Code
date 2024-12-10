// P2495 
// 虚树是一种树上dp思想而非具体方法，保留对dp信息有用的少部分结点来降低时间复杂度
// 具体特征表现为有用点的数量在题目中有明确限制
// 本题中只保留关键点和关键点之间的lca来建树

#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2.5e5+7, M = 5e5+7;

int n;
int stk[N],fa[N][20],dfn[N],dep[N],lst[N],flg[N],minv[N];
int timer;

struct MAP{
	struct EDGE{
		int to,nxt,val;
	}e[M<<1];
	int h[N],qcnt;
}ori,cur;

void addedge(int x,int y,int z,MAP &tmp)
{
	tmp.e[++tmp.qcnt] ={y,tmp.h[x],tmp.qcnt};
	tmp.h[x] = tmp.qcnt;
}

void dfs1(int x,int fat)
{
	dfn[x] = ++timer;
	fa[x][0] = fat;
	dep[x] = dep[fat] + 1;
	for(int i = ori.h[x]; i; i = ori.e[i].nxt)
	{
		int v = ori.e[i].to;
		if(v!=fat) 
		{
			minv[v] = min(minv[x],ori.e[i].val);
			dfs1(v,x);
		}
	}
}

void build_lca()
{
	for(int i=1;i<20;++i)
	{
		for(int j = i; j <= n; ++j)
		{
			fa[j][i] = fa[fa[j][i-1]][i-1];
		}
	}
}

int dfs2(int x)
{
	int sum = 0;
	for(int i = cur.h[x]; i; i = cur.e[i].nxt)
	{
		int v = cur.e[i].to;
		sum += dfs2(v);
	}
	int res;
	if(flg[x]) res = minv[x];
	else res = min(minv[x],sum);

	flg[x] = 0;
	cur.h[x] = 0;
	
	return res;
}

int LCA(int x,int y)
{
	if(dep[x] < dep[y]) swap(x,y);
	for(int i=19;~i;i--)
	{
		if(fa[x][i] !=0 && dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	}
	for(int i=19;~i;i--)
	{
		if(fa[x][i] !=0 && fa[y][i] !=0 && fa[x][i] != fa[y][i])
		{
			x = fa[x][i], y = fa[y][i];
		}
	}
	return fa[y][0];
}

void solv()
{
	minv[1] = LONG_LONG_MAX;
	cin>>n;
	for(int i = 1; i <= n; ++i) fa[i][0] = i;
	for(int i = 1; i < n; i++)
	{
		int u,v,w; cin>>u>>v>>w;
		addedge(u,v,w,ori);
	}
	dfs1(1,0);
	build_lca();
	int m; cin>>m;
	while(m--)
	{
		int k; cin>>k;
		for(int i = 1; i <= k; ++i)
		{
			cin>>lst[i]; flg[lst[i]] = 1;
		}
		function<bool(int,int)> cmp = [&](int x,int y){return dfn[x]<dfn[y];};
		sort(lst+1,lst+k+1,cmp);
		int tp = 1;
		stk[tp] = lst[1];
		for(int i = 2; i <= k; ++i)
		{
			int lca = LCA(stk[tp],lst[i]);
			while(1)
			{
				if(lca == stk[tp]) break;
				if(dep[lca] < dep[stk[tp-1]])
				{
					addedge(stk[tp-1],stk[tp],0,cur);
					tp--;
				}
				else //dep[lca] > dep[stk[tp-1]]
				{
					addedge(lca,stk[tp],0,cur);
					if(lca != stk[tp-1]) stk[tp] = lca;
					else tp--;
				}
			}
			stk[++tp] = lst[i];
		}
		dfs2(stk[1]);
	}
}



signed main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	solv();
	return 0;
}