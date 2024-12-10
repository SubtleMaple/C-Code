#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5+7,inf = 2e9;

int n,fa[N],ch[N][2],siz[N],c[N],val[N],rt,tot;

#define ls(x) ch[x][0]
#define rs(x) ch[x][1]



void psup(int x){
    siz[x] = siz[ls(x)]+siz[rs(x)]+c[x];
}

bool dit(int x){
    return val[x] > val[fa[x]];
}

void connect(int x,int f,int d)
{
    fa[x] = f, ch[f][d] = x;
}

int nw(int v,int f)
{
    val[++tot] = v;
    siz[tot] = c[tot] = 1;
    connect(tot,f,v > val[f]);
    return tot;
}

void rotate(int x)
{
    int f = fa[x],d1 = dit(x),d2 = dit(f);
    connect(ch[x][d1^1],f,d1);
    connect(x,fa[f],d2);
    connect(f,x,d1^1);
    psup(f),psup(x);
}

void splay(int x,int sig)
{
    int f;
    while(fa[x] != sig)
    {
        f = fa[x];
        if(fa[f]!=sig)
        {
            rotate(dit(x)==dit(f) ? f : x);
        }
        rotate(x);
    }
    if(!sig) rt = x;
}

int find(int v)
{
    int x = rt;
    while(val[x] != v && ch[x][v>val[x]]) x = ch[x][v>val[x]];
    return x;
}

int prenxt(int v,int op)
{
    splay(find(v),0);
    int x = rt;
    if((val[x] < v && !op) || (val[x] > v && op)) return x;
    x = ch[x][op];
    while(ch[x][op^1]) x = ch[x][op^1];
    return x;
}

int getrk(int v)
{
    splay(find(v),0);
    return siz[ls(rt)]+1;
}

int kth(int rk)
{
    int x = rt;
    while(1)
    {
        if(rk <= siz[ls(x)]) x = ls(x);
        else
        if(rk > siz[ls(x)]+c[x])
        {
            rk-=siz[ls(x)]+c[x];
            x = rs(x);
        }
        else return val[x];
    }
}



void insert(int v)
{
    int x = rt, tmp = 0;
    while(x && val[x] != v) tmp = x, x = ch[x][v > val[x]];
    if(!x) x = nw(v,tmp);
    else c[x]++;
    splay(x,0);
}

void del(int v)
{
    int pre = prenxt(v,0),nxt = prenxt(v,1);
    splay(pre,0),splay(nxt,pre);
    if(c[ls(nxt)]>1) c[ls(nxt)]--,splay(ls(nxt),0);
    else ls(nxt) = 0;
}

signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int op,ans,x;
	cin>>n;
	insert(-inf),insert(inf);
	while(n--)
	{
		cin>>op>>x;
		if(op==1) insert(x);
		if(op==2) del(x);
		if(op==3) ans=getrk(x)-1;
		if(op==4) ans=kth(x+1);
		if(op==5) ans=val[prenxt(x,0)];
		if(op==6) ans=val[prenxt(x,1)];
		if(op>2) cout<<ans<<'\n';
	}
    return 0;
}

