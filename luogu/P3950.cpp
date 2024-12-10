#include<iostream>

using namespace std;

const  int N = 1e6+7;

int n,m,war[N][2],war_cnt;

int ch[N][2],fa[N],lzr[N];

#define ls(x) ch[x][0]
#define rs(x) ch[x][1]

bool isroot(int x){
	return ls(fa[x]) != x && rs(fa[x]) != x;
}

void psrev(int x)
{
	if(!x) return;
	swap(ch[x][0],ch[x][1]);
	lzr[x] ^= 1;
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
	for(int s = 0; x; s = x, x = fa[x]){
		splay(x);
		rs(x) = s;
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

void link(int x,int y){
	makeroot(x);
	if(findroot(y) != x) fa[x] = y;
}

// void cut(int x,int y){
// 	makeroot(x);
// 	if(findroot(y)!=x || fa[y] != x || ls(y)) return;
// 	fa[y] = rs(x) = 0;
// }
void cut(int x,int y){
	makeroot(x); access(y);
	fa[x] = ls(y) = 0;
}


int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n>>m;
	for(int i = 1; i < n; ++i)
	{
		int u,v; cin>>u>>v;
		link(u,v);
	}
	for(int i=1;i<=m;++i)
	{
		char ch; cin>>ch;
		if(ch=='Q'){
			int x,y; cin>>x>>y;
			makeroot(x); access(y);
			cout<<(findroot(y)==x ? "Yes\n" : "No\n");
		}
		else if(ch=='C'){
			int x,y; cin>>x>>y;
			cut(x,y);
			war[++war_cnt][0] = x, war[war_cnt][1] = y;
		}
		else{
			int x; cin>>x;
			link(war[x][0],war[x][1]);
		}
	}

	return 0;
}