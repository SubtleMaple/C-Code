// 判断边 (x,y) 是否属于所有给定路径的交集
// 发现以x为根时，每个给定路径有一个端点在y和其子树中
// 所以对每个路径的两端点异或一个随机权值，维护y的子树的异或和，
// 若这个异或和等于所有给定路径的权值异或和，
// 说明y包含每个路径的其中一个端点
// 具体地，makeroot(x),splay(y),则提取出了(x,y)这条边，以x为根，y的所有子树在lct中都变成了y的虚儿子
// x的虚儿子此时是y子树以外的其他x的子树，
// x 和 y的虚儿子分别含有路径端点的一半，都可以使用



#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define int long long

using namespace std;

const int N = 3e5+7, M = 3e5+7;

int n,m,allsum,scnt;

int ch[N][2],fa[N],val[N],sum[N],sum2[N],lzr[N];
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
struct PATH{
	int x,y,val;
}S[M];

mt19937 rnd(time(0));

bool isroot(int x){
	return ls(fa[x]) != x && rs(fa[x]) != x;
}

void psup(int x)
{
	sum[x] = val[x] ^ sum[ls(x)] ^ sum[rs(x)] ^ sum2[x];
}

void psrev(int x){
	if(!x) return;
	swap(ls(x),rs(x));
	lzr[x] ^= 1;
}

void psdn(int x){
	if(lzr[x]){
		psrev(ls(x)),psrev(rs(x));
		lzr[x] = 0;
	}
}

void rotate(int x)
{
	int y = fa[x], z = fa[y];
	int k = ch[y][1] == x;
	if(!isroot(y)) ch[z][ch[z][1] == y] = x;
	fa[x] = z;
	ch[y][k] = ch[x][k^1];
	fa[ch[x][k^1]] = y;
	ch[x][k^1] = y;
	fa[y] = x;
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
			rotate(((ls(y)==x)^(ls(z)==y)) ? x : y);
		rotate(x);
	}
}

void access(int x){
	int z = x;
	for(int sn = 0; x; sn = x, x = fa[x]){
		splay(x);
		sum2[x] ^= sum[sn];
		sum2[x] ^= sum[rs(x)];
		rs(x) = sn;
		psup(x);
	}
	splay(z);
}

void makeroot(int x){
	access(x); psrev(x);
}

void split(int x,int y){
	makeroot(x),access(y);
}

int findroot(int x){
	access(x);
	while(ls(x)) psdn(x), x = ls(x);
	splay(x);
	return x;
}

void link(int x,int y)
{
	// makeroot(x);
	// if(findroot(y) != x){
	// 	fa[x] = y;
	// 	sum2[y] ^= sum[x];
	// 	psup(y); // 
	// }
	split(x,y);
	fa[x] = y; sum2[y] ^= sum[x]; 
	psup(y);
}

void cut(int x,int y)
{
	split(x,y);
	ls(y) = fa[x] = 0; 
	psup(y);
}

void Modify(int x,int v)
{
	access(x); val[x] ^= v;
	psup(x);
}

signed main()
{
	int test_id; cin>>test_id;
	cin>>n>>m;
	rep(i,1,n-1){
		int x,y; cin>>x>>y;
		link(x,y);
	}
	rep(i,1,m){
		int typ; cin>>typ;
		if(typ == 1){
			int x,y,u,v; cin>>x>>y>>u>>v;
			cut(x,y), link(u,v);
		}
		else if(typ == 2){
			int x,y; cin>>x>>y;
			int v = rnd();
			S[++scnt] = (PATH){x,y,v};
			allsum ^= v;
			Modify(x,v), Modify(y,v);
		}
		else if(typ == 3){
			int id; cin>>id;
			int x = S[id].x, y = S[id].y, v = S[id].val;
			allsum ^= v;
			Modify(x,v), Modify(y,v);
		}
		else if(typ == 4){
			int x,y; cin>>x>>y;
			split(x,y);
			splay(x); // 此处无论以谁为splay的根，另一个点的sum都表示它的与另一点无关的子树
			// x 和 y的子树分别占据路径的一半端点，都可以使用
			if(sum[y] == allsum) cout<<"YES\n"; 
			// 此处是使用y的虚儿子，需要把x旋转到根，否则y的信息中会包含x的信息
			else cout<<"NO\n";
		}
	}
	return 0;
}