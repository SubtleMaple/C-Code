#include<iostream>
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;

const int N = 1e6 + 7, M = 1e6 + 7;

int n,m;

int ch[N][2],fa[N],mxid[N],val[N],lzr[N];
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]

bool isroot(int x){
	return ls(fa[x]) != x && rs(fa[x]) != x;
}

void psrev(int x){
	if(!x) return;
	swap(ch[x][0],ch[x][1]);
	lzr[x] ^= 1;
}

void psdn(int x){
	if(!lzr[x]) return;
	psrev(ls(x)),psrev(rs(x));
	lzr[x] = 0;
}

void psup(int x){
	mxid[x] = x;
	if(ls(x) && val[mxid[ls(x)]] > val[mxid[x]]) mxid[x] = mxid[ls(x)];
	if(rs(x) && val[mxid[rs(x)]] > val[mxid[x]]) mxid[x] = mxid[rs(x)];
}

void rotate(int x){
	int y = fa[x], z = fa[y];
	int k = ch[y][1] == x;
	if(!isroot(y)) ch[z][ch[z][1] == y] = x;
	fa[x] = z;
	ch[y][k] = ch[x][k^1];
	fa[ch[x][k^1]] = y;
	fa[y] = x;
	ch[x][k^1] = y;

	psup(y), psup(x);
}

int stk[N];

void splay(int x){
	int r = x, tp = 0;
	stk[++tp] = r;
	while(!isroot(r)) r = fa[r], stk[++tp] = r;
	while(tp) psdn(stk[tp--]);

	while(!isroot(x)){
		int y = fa[x], z = fa[y];
		if(!isroot(y))
			((rs(y)==x)^(rs(z)==y)) ? rotate(x) : rotate(y);
		rotate(x);
	}
}

void access(int x){
	int z = x;
	for(int s = 0; x; s = x, x = fa[x])
	{
		splay(x);
		rs(x) = s;
		psup(x);
	}
	splay(z);
}

void makeroot(int x){
	access(x); psrev(x);
}

int findroot(int x){
	access(x);
	while(ls(x)) psdn(x), x = ls(x);
	splay(x);
	return x;
}

void split(int x,int y){
	makeroot(x), access(y);
}

void link(int x,int y){
	makeroot(x); fa[x] = y;
}

signed main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int ans = 0,cnt = 0;
	cin>>n>>m;
	rep(i,1,m){
		int x,y,z;
		cin>>x>>y>>z;
		if(x==y) continue;
		val[i+n] = z;
		makeroot(x);
		if(findroot(y) != x){
			link(i+n,x),link(i+n,y);
			ans += z;
			cnt++;
		}
		else
		{
			makeroot(x); access(y);
			int ep = mxid[y];
			if(z < val[ep])
			{
				splay(ep); // 修改前一定要splay！！！
				fa[ls(ep)] = fa[rs(ep)] = 0;
				link(i+n,x),link(i+n,y);
				ans -= val[ep];
				ans += z;
			}
		}
	}
	if(cnt == n - 1) cout<< ans;
	else cout<<"orz";
 
	return 0;
}