#include<iostream>
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define int long long
using namespace std;

const int N = 1e5+7;
const int mod = 51061;

void Mod(int &x){
	x%mod;
}

struct TREE
{
	int fa,ch[2],val,sum,sz;
	int lz,add,mul;
}t[N];

void update(int x) {
    t[x].sum = (t[x].val + t[t[x].ch[0]].sum + t[t[x].ch[1]].sum) % mod;
    t[x].sz = t[t[x].ch[0]].sz + t[t[x].ch[1]].sz + 1;
}

void psrev(int x)
{
	swap(t[x].ch[0],t[x].ch[1]);
	t[x].lz ^= 1;
}

void use_tag(int x, int add, int mul) {
    t[x].val = (t[x].val * mul + add) % mod;
    t[x].add = (t[x].add * mul + add) % mod;
    t[x].mul = (t[x].mul * mul) % mod;
    t[x].sum = (t[x].sum * mul + t[x].sz * add)%mod;
}

void psdn(int x)
{
	use_tag(t[x].ch[0],t[x].add,t[x].mul);
	use_tag(t[x].ch[1],t[x].add,t[x].mul);
	t[x].add = 0, t[x].mul = 1;
	if(t[x].lz)
	{
		psrev(t[x].ch[0]),psrev(t[x].ch[1]);
		t[x].lz = 0;
	}
	
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

void do_add(int x,int y,int c)
{
	makeroot(x); access(y);
	// t[y].val += c;
	// t[y].add += c;
	// update(y);
	use_tag(y,c,1);
}

void do_mul(int x,int y,int c)
{
	makeroot(x); access(y);
	// t[y].val *= c;
	// t[y].add *= c;
	// t[y].mul *= c;
	// update(y);
	use_tag(y,0,c);
}

signed main()
{
	int n,m;
	cin>>n>>m;
	rep(i,1,n) t[i].val = t[i].mul = t[i].sz = 1;
	rep(i,1,n-1)
	{
		int u,v;cin>>u>>v;
		link(u,v);
	}
	while(m--)
	{
		char ch; cin>>ch;
		if(ch=='+') 
		{
			int u,v,c;cin>>u>>v>>c;
			do_add(u,v,c);
		}
		if(ch=='*')
		{
			int u,v,c;cin>>u>>v>>c;
			do_mul(u,v,c);
		}
		if(ch=='-')
		{
			int u,v,x,y;cin>>u>>v>>x>>y;
			cut(u,v),link(x,y);
		}
		if(ch=='/')
		{
			int u,v;cin>>u>>v;
			makeroot(u);access(v);
			cout<<t[v].sum<<'\n';
		}
	}
	
	return 0;
}