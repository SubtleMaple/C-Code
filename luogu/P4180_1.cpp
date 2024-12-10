#include<iostream>
#include<map>
#include<algorithm>
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i) 
#define pii pair<int,int>

using namespace std;

const int N = 1e6 + 7, M = 1e6 + 7;

int n,m,q;

int ch[N][2],fa[N],mx[N],nmx[N],val[N],lzr[N],dsu[N],res,ans,ecnt;
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
	int cnt=0;
	int tmp[6];
	rep(i,1,5) tmp[i] = -1e18;
	mx[x] = nmx[x] = -1;
	tmp[++cnt] = val[x];
	if(ls(x)){
		tmp[++cnt] = mx[ls(x)];
		if(~nmx[ls(x)]) tmp[++cnt] = nmx[ls(x)];
	}
	if(rs(x)){
		tmp[++cnt] = mx[rs(x)];
		if(~nmx[rs(x)]) tmp[++cnt] = nmx[rs(x)];
	}
	sort(tmp+1,tmp+cnt+1,greater<int>());
	mx[x] = tmp[1];
	rep(i,2,cnt) if(tmp[i] < mx[x]) {
		nmx[x] = tmp[i]; break;
	}
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

int find_dsu(int x){
	return x == dsu[x] ? x : dsu[x] = find_dsu(dsu[x]);
}

//map<pii,int> id_edge;

signed main()
{
	freopen("data.in","r",stdin);
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n>>m;
	rep(i,1,n) dsu[i] = i, val[i] = -1e18;
	rep(i,1,m){
		int x,y,z; cin>>x>>y>>z;
		if(x > y) swap(x,y);
		e[i] = (EDGE){x,y,z};
		//id_edge[make_pair(x,y)] = i;
	}

	sort(e+1,e+m+1,cmp);

	rep(i,1,m){
		if(e[i].x==e[i].y) continue;
		val[i+n] = e[i].z;
		int x = find_dsu(e[i].x), y = find_dsu(e[i].y);
		if(x==y) continue;
		link(e[i].x,i + n), link(e[i].y,i + n);
		vis[i] = 1;
		dsu[x] = y;
		++ecnt; res += e[i].z;
		if(ecnt == n-1) break;
	}
	ans = 1e18;
	rep(i,1,m) if(!vis[i])
	{
		if(e[i].x==e[i].y) continue;
		int x = e[i].x, y = e[i].y;
		split(x,y);
		//ans = min(ans,e[i].z - (e[i].z > val[mx[y]] ? val[mx[y]] : val[nmx[y]]));
		// ans = min(ans,e[i].z - (e[i].z > mx[y] ? mx[y] : nmx[y]));
		if(e[i].z > mx[y]) ans = min(ans,e[i].z - mx[y]);
		else if(nmx[y] >=0 && e[i].z > nmx[y]) ans = min(ans,e[i].z - nmx[y]);
	}
	cout << res + ans;
	return 0;
}