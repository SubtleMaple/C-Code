#include<iostream>

using namespace std;

const int N = 2e6+7;

int a[N],b[N][2],fa[N],ch[N][2],s[N];
int g[N][3];
int n,m;

#define ls(x) ch[x][0]
#define rs(x) ch[x][1]

bool isroot(int x){
	return ls(fa[x])!=x && rs(fa[x])!=x;
}

void psup(int x){
	b[x][0] = s[x] >= 2;
	b[x][1] = s[x] >= 1;
	if(rs(x))
	{
		if(b[rs(x)][0]) b[x][0] = b[x][1];
		else if(!b[rs(x)][1]) b[x][1] = b[x][0];
	}
	if(ls(x))
	{
		if(b[x][0]) b[x][0] = b[x][1] = b[ls(x)][1];
		else if(!b[x][1]) b[x][0] = b[x][1] = b[ls(x)][0];
		else b[x][0] = b[ls(x)][0], b[x][1] = b[ls(x)][1];
	}
}

void rotate(int x){
	int y = fa[x], z = fa[y];
	int k = ch[y][1]==x;
	if(!isroot(y)) ch[z][ch[z][1]==y] = x;
	fa[x] = z;

	ch[y][k] = ch[x][k^1];
	fa[ch[x][k^1]] = y;

	ch[x][k^1] = y;
	fa[y] = x;
	psup(y), psup(x);
}

void splay(int x)
{
	while(!isroot(x))
	{
		int y = fa[x], z = fa[y];
		if(!isroot(y))
			((rs(z)==y)^(rs(y)==x)) ? rotate(x) : rotate(y);
		rotate(x);
	}
}

void access(int x)
{
	int z = x;
	for(int sn = 0; x; sn = x, x = fa[x])
	{
		splay(x);
		// 原先实边变虚边，从s中加上
		s[x] += b[rs(x)][0];
		s[x] -= b[sn][0];
		rs(x) = sn;
		psup(x);
	}
	splay(z);
}

void dfs(int x)
{
	for(int i = 0; i < 3; ++i)
	{
		if(g[x][i] <= n) dfs(g[x][i]);
		s[x] += a[g[x][i]];
	}
	b[x][0] = a[x] = s[x] >= 2;
	b[x][1] = s[x] >= 1;
}


int main()
{
	cin>>n;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			cin>>g[i][j];
			fa[g[i][j]] = i;
		}
	}
	for(int i = n + 1; i <= 3 * n + 1; ++i) cin>>a[i];
	dfs(1);
	cin>>m;
	while(m--)
	{
		int x; cin>>x;
		access(fa[x]);
		a[x] ^= 1;
		a[x] ? ++s[fa[x]] : --s[fa[x]];
		//psup(x);
		access(1);
		cout<<b[1][0]<<'\n';
	}
	return 0;
}