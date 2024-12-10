#include<iostream>
#include<map>
#include<algorithm>
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i) 
#define pii pair<int,int>

using namespace std;

const int N = 1e6 + 7, M = 1e6 + 7;

int n,m,q;

int ch[N][2],fa[N],mn[N],val[N],lzr[N],ans,ecnt;
bool vis[M];
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

void psup(int x)
{
	mn[x] = x;
	if(ls(x) && val[mn[x]] > val[mn[ls(x)]]) mn[x] = mn[ls(x)];
	if(rs(x) && val[mn[x]] > val[mn[rs(x)]]) mn[x] = mn[rs(x)];
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

struct EDGE{
	int x,y,z;
}e[M];

bool cmp(EDGE a,EDGE b){
	return a.z < b.z;
}

signed main()
{
	//freopen("data.in","r",stdin);
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n>>m;
	rep(i,1,n) val[i] = 1e18;
	rep(i,1,m){
		int x,y,z; cin>>x>>y>>z;
		if(x > y) swap(x,y);
		e[i] = (EDGE){x,y,z};
	}

	sort(e+1,e+m+1,cmp);

	int idx_mn = 0;
	int ans = 1e9;

	rep(i,1,m){
		if(e[i].x==e[i].y) continue;
		val[i+n] = e[i].z;
		int x = e[i].x , y = e[i].y;
		makeroot(x);
		if(findroot(y)==x) {
			split(x,y);
			int id = mn[y];
			splay(id);
			fa[ls(id)] = fa[rs(id)] = 0;
			vis[id-n] = 0;
			link(e[i].x,i + n), link(i + n,e[i].y);
			vis[i] = 1;
		}
		else
		{
			link(e[i].x,i + n), link(i + n,e[i].y);
			vis[i] = 1;
			++ecnt;
		}
		while(!vis[idx_mn]) idx_mn++;
		if(ecnt == n - 1) ans = min(ans,e[i].z - e[idx_mn].z);
	}
	cout<<ans;
	return 0;
}