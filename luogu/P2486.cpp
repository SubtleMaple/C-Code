#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
const int N = 1e5+7;
struct TREE{
    int fa,ch[2],col,sum,lzr,lzc,Lc,Rc;
}t[N];

bool isroot(int x)
{
    return t[t[x].fa].ch[0]!=x && t[t[x].fa].ch[1]!=x;
}

void psup(int x)
{
    t[x].Lc = t[x].ch[0] ? t[t[x].ch[0]].Lc : t[x].col;
    t[x].Rc = t[x].ch[1] ? t[t[x].ch[1]].Rc : t[x].col;
    if(t[x].ch[0] && t[x].ch[1])
    {
        t[x].sum = t[t[x].ch[0]].sum + t[t[x].ch[1]].sum + 1 - (t[t[x].ch[0]].Rc == t[x].col) 
                   - (t[t[x].ch[1]].Lc == t[x].col);
    }
    else if(t[x].ch[0] && !t[x].ch[1])
    {
        t[x].sum = t[t[x].ch[0]].sum + (t[t[x].ch[0]].Rc != t[x].col);
    }
    else if(!t[x].ch[0] && t[x].ch[1])
    {
        t[x].sum = t[t[x].ch[1]].sum + (t[t[x].ch[1]].Lc != t[x].col);
    }
    else t[x].sum = 1;
}

void pscol(int x,int col)
{
    if(!x) return;
    t[x].col = col;
    t[x].lzc = t[x].Lc = t[x].Rc = col;
    t[x].sum = 1;
}

void psrev(int x)
{
    if(!x) return;
    swap(t[x].ch[0],t[x].ch[1]);
    swap(t[x].Lc,t[x].Rc); // 注意也要换最左和最右颜色
    t[x].lzr ^= 1;
}

void psdn(int x)
{
    if(t[x].lzr)
    {
        psrev(t[x].ch[0]); psrev(t[x].ch[1]);
        t[x].lzr = 0;
    }
    if(t[x].lzc) {
        pscol(t[x].ch[0],t[x].lzc);
        pscol(t[x].ch[1],t[x].lzc);
        t[x].lzc = 0;
    }
}

void rotate(int x){
    int y = t[x].fa, z = t[y].fa;
    int k = t[y].ch[1]==x;
    if(!isroot(y)) t[z].ch[t[z].ch[1]==y] = x;
    t[x].fa = z;

    t[y].ch[k] = t[x].ch[k^1];
    t[t[x].ch[k^1]].fa = y;

    t[x].ch[k^1] = y;
    t[y].fa = x;
    psup(y),psup(x);
}

int stk[N];

void splay(int x)
{
    int r = x, tp = 0;
    stk[++tp] = r;
    while(!isroot(r)) r = t[r].fa, stk[++tp] = r;
    while(tp) psdn(stk[tp--]);

    while(!isroot(x))
    {
        int y = t[x].fa, z = t[y].fa;
        if(!isroot(y))
        {
            ((t[z].ch[1]==y)^(t[y].ch[1]==x)) ? rotate(x) : rotate(y);
        }
        rotate(x);
    }
}

void access(int x)
{
    int z = x;
    for(int s=0; x; s = x, x = t[x].fa) //
    {
        splay(x); t[x].ch[1] = s; psup(x);
    }
    splay(z);
}

void makeroot(int x)
{
    access(x);
    psrev(x);
}

void link(int x,int y)
{
    makeroot(x); t[x].fa = y;
}


int main()
{
    int n,m;
    cin>>n>>m;
    rep(i,1,n) {
        cin>>t[i].col;
        t[i].Lc = t[i].Rc = t[i].col;  
        t[i].sum = 1;
    }
    rep(i,1,n-1) {
        int u,v; cin>>u>>v;
        link(u,v);
    }
    while(m--)
    {
        char ch; cin>>ch;
        if(ch=='C') {
            int x,y,col; cin>>x>>y>>col;
            makeroot(x); access(y); pscol(y,col);
        }
        else {
            int x,y; cin>>x>>y;
            makeroot(x); access(y); cout<<t[y].sum<<'\n';
        }
    }
    return 0;
}