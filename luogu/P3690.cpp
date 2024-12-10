#include<iostream>

using namespace std;

const int N = 1e5+7;

struct TREE
{
	int fa,ch[2],val,sum,lz;
}t[N];

void update(int x)
{
	t[x].sum = t[x].val ^ t[t[x].ch[0]].sum ^ t[t[x].ch[1]].sum;
}

void psrev(int x)
{
	swap(t[x].ch[0],t[x].ch[1]);
	t[x].lz ^= 1;
}

void psdn(int x)
{
	if(!t[x].lz) return;
	psrev(t[x].ch[0]),psrev(t[x].ch[1]);
	t[x].lz = 0;
}

bool isroot(int x)
{
	return (t[t[x].fa].ch[0] != x)&&(t[t[x].fa].ch[1] != x);
}

// void rotate(int x)
// {
// 	int p = t[x].fa, g = t[p].fa;
// 	int k = (t[p].ch[1] == x);
// 	//if(!g) t[g].ch[t[g].ch[1] == p] = x;
// 	if(!isroot(y)) t[g].ch[t[g].ch[1] == p] = x;
// 	t[x].fa = g;

// 	t[y].ch[k] = t[x].ch[k^1];
// 	t[t[x].ch[k^1]].fa = y;

// 	t[y].fa = x;
// 	t[x].ch[k^1] = y;
// 	update(y), update(x);
// }

void rotate(int x)
{
	int y = t[x].fa, z = t[y].fa;
	int k = (t[y].ch[1] == x);
	if(!isroot(y)) t[z].ch[t[z].ch[1] == y] = x;
	t[x].fa = z;

	t[y].ch[k] = t[x].ch[k^1];
	t[t[x].ch[k^1]].fa = y;

	t[x].ch[k^1] = y;
	t[y].fa = x;

	update(y), update(x);
}

// 非 LCT 版 splay
// void splay(int x)
// {
// 	while(t[x].fa)
// 	{
// 		int p = t[x].fa, g = t[p].fa;
// 		if(t[p].fa)
// 		{
// 			if((t[p].ch[0] == x) ^ (t[g].ch[0] == p)) rotate(p);
// 			else rotate(x);
// 		}
// 		rotate(x);
// 	}
// }

// LCT 版 splay
// splay 前必须刷新所有 x 路径上的翻转标记

int stk[N];

void splay(int x)
{

	int tp = 0, r = x;
	stk[++tp] = r;
	while(!isroot(r)) r = t[r].fa, stk[++tp] = r; // 父亲后入栈
	while(tp) psdn(stk[tp]), tp--; // 从父亲到儿子使用翻转标记

	while(!isroot(x))
	{
		int y = t[x].fa, z = t[y].fa;
		if(!isroot(y))
		{
			((t[y].ch[1]==x) ^ (t[z].ch[1] == y)) ? rotate(x) : rotate(y);
		}
		rotate(x);
	}
}

void access(int x)
{
	int z = x;
	for(int s = 0; x; s = x, x = t[x].fa)
		splay(x), t[x].ch[1] = s, update(x);
	splay(z);
}

void makeroot(int x)
{
	access(x);
	psrev(x);
}

int findroot(int x)
{
	access(x);
	while(t[x].ch[0]) psdn(x),x = t[x].ch[0];
	splay(x);
	return x;
}

void split(int x,int y)
{
	makeroot(x);
	access(y);
}



void link(int x,int y)
{
	makeroot(x);
	if(findroot(y) != x) t[x].fa = y;
	
}

void cut(int x,int y)
{
	makeroot(x);
	if(findroot(y) ==x && t[y].fa == x && !t[y].ch[0]) {
		t[x].ch[1] = t[y].fa = 0;
		update(x);
	}
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>t[i].val;
	for(int i=1;i<=m;++i)
	{
		int o,x,y; cin>>o>>x>>y;
		if(o==0)
		{
			split(x,y); cout<<t[y].sum<<'\n';
		}
		if(o==1)
		{
			link(x,y);
		}
		if(o==2)
		{
			cut(x,y);
		}
		if(o==3)
		{
			splay(x); t[x].val = y; update(x);
		}
	}
	return 0;
}