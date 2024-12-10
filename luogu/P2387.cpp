// 本题做法，将边按 a权值从小到大排序，从所有点孤立开始每次尝试加入一条边
// 对b权值动态维护最小生成树
//	若新加入的边 (x,y) ，x和y已联通，则看该边的 b 是否小于xy已有路径的b，否则不加入该边
// 若小于，则加入该边，删去xy原路径最大b的边
// 每次加边后，若1与n联通，则用当前的 a 和 1到n路径最大的b更新答案

// 因为如果新加入的边不在1到n的路径，则 1到n 的 max_b 不变，
// 由于 a 升序排列，所以当前的 a + max_b 大于 原先的 a + max_b，答案不会更新

// 如果新加入的边在1到n的路径，新加入的边 a 最大，所以用这个 a + max_b 尝试更新答案

// 总而言之，无论新加入的边是否在 1 到 n 的路径上，都可把它的a当做最大的 a 更新答案
// 因为它是当前最大的 a，它不在路径上时一定不会更新答案，
// 它在路径上时它就是路径上最大的a，更新答案自然是成立的
#include<iostream>
#include<map>
#include<algorithm>
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i) 
#define pii pair<int,int>

using namespace std;

const int N = 5e5 + 7, M = 5e5 + 7;

int n,m,q;

int ch[N][2],fa[N],mx[N],val[N],lzr[N],ans = 1e9,ecnt;
bool vis[M];
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]

bool isroot(int x){
	if(!fa[x]) return 1;
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
	mx[x] = x;
	if(ls(x) && val[mx[x]] < val[mx[ls(x)]]) mx[x] = mx[ls(x)];
	if(rs(x) && val[mx[x]] < val[mx[rs(x)]]) mx[x] = mx[rs(x)];
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
	int x,y,a,b;
}e[M];

bool cmp(EDGE u,EDGE v){
	return u.a < v.a;
}


signed main()
{
	//freopen("data.in","r",stdin);
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n>>m;
	rep(i,1,m){
		int x,y,a,b;
		cin>>x>>y>>a>>b;
		if(x > y) swap(x,y);
		e[i] = (EDGE){x,y,a,b};
	}

	sort(e+1,e+m+1,cmp);

	rep(i,1,m){
		if(e[i].x == e[i].y) continue;
		val[i+n] = e[i].b;
		int x = e[i].x, y = e[i].y;
		makeroot(x);
		if(findroot(y) != x) {
			link(x,i+n), link(i+n,y);
		}
		else
		{
			split(x,y);
			int id = mx[y]; 
			// 注意此处mx[y]是变化的值，id只是y为根时的值，所以下方不可用mx[y]
			// 若 RE 则就是这个问题导致的
			if(val[id] <= e[i].b) continue;
			splay(id);
			fa[ls(id)] = fa[rs(id)] = 0;
			link(x,i+n), link(i+n,y);	
		}
		makeroot(1);
		if(findroot(n)==1)
		{
			split(1,n);
			ans = min(ans,e[i].a + val[mx[n]]);
		}
	}
	if(ans == 1e9) ans = -1;
	cout<<ans;
	return 0;
}