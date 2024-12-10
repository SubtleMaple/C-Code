#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;

const  int N = 2e5+7;

int n,m;

int ch[N][2],fa[N],lzr[N],dsu[N],dsu_siz[N],sum[N];
int num[N];

#define ls(x) ch[x][0]
#define rs(x) ch[x][1]

int find_dsu(int x){
	return x==dsu[x] ? x : dsu[x] = find_dsu(dsu[x]);
}

bool isroot(int x){
	return ls(fa[x]) != x && rs(fa[x]) != x;
}

void psrev(int x)
{
	if(!x) return;
	swap(ch[x][0],ch[x][1]);
	lzr[x] ^= 1;
}
void psup(int x){
	sum[x] = dsu_siz[x] + sum[ls(x)] + sum[rs(x)];
}

void psdn(int x)
{
	if(lzr[x]){
		psrev(ls(x)),psrev(rs(x));
		lzr[x] = 0;
	}
}

void rotate(int x)
{
	int y = fa[x], z = fa[y], k = ch[y][1] == x;
	if(!isroot(y)) ch[z][ch[z][1]==y] = x;
	fa[x] = z;
	ch[y][k] = ch[x][k^1];
	fa[ch[x][k^1]] = y;

	ch[x][k^1] = y;
	fa[y] = x;
	psup(y), psup(x);
}

int stk[N];

void splay(int x)
{
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
	for(int s = 0; x; s = x, x = fa[x] = find_dsu(fa[x])){ // 由于缩点，所以x要跳到fa[x]的代表元素
		splay(x);
		rs(x) = s;
		psup(x);
	}
	splay(z);
}

void makeroot(int x){
	access(x);
	psrev(x);
}

int findroot(int x){
	access(x);
	while(ls(x)) psdn(x),x = ls(x);
	splay(x);
	return x;
}



void dfs(int x,int f)
{
	if(!x) return;
	dsu[x] = f;
	dsu_siz[f] += dsu_siz[x];
	dfs(ls(x),f), dfs(rs(x),f);
}

void link(int x,int y){
	x = find_dsu(x), y = find_dsu(y);
	if(x == y) return; //
	makeroot(x);
	if(findroot(y) != x) fa[x] = y;
	else
	{
		dfs(rs(x),x);
		rs(x) = 0;
		psup(x);
	}
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n>>m;
	rep(i,1,n) {
		cin>>num[i]; dsu[i] = i;
		dsu_siz[i] = num[i];
	}
	rep(oo,1,m)
	{
		int op,x,y;
		cin>>op>>x>>y;
		if(op == 1){
			link(x,y);
		}
		else if(op == 2){
			int xx = find_dsu(x);
			splay(xx); // 修改结点信息前必须splay到根部
			dsu_siz[xx] -= num[x];
			num[x] = y;
			dsu_siz[xx] += num[x];
			psup(xx);
		}
		else if(op == 3){
			x = find_dsu(x),y = find_dsu(y);
			makeroot(x); 
			if(findroot(y) == x){
				cout<<sum[x]<<'\n';
			}
			else if(findroot(y) != x){
				cout<<-1<<'\n';
			}
			else{
				access(y);
				cout<<sum[y]<<'\n';
			}
			
		}

	}

	
	
	return 0;
}