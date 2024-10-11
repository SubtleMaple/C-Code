#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define int long long

const int N = 1e5+7;

int n,m,mod,a[N];

// lazy tag 是给子节点用的，不是给自己用的
struct Tree{
    int sum;
    int lz,mul,l,r;
}tr[N<<2];

#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

void Mod(int &x){
    x %= mod;
}

void psup(int x)
{
    Mod(tr[x].sum = tr[ls(x)].sum + tr[rs(x)].sum);
}

void build(int x,int l,int r)
{
    tr[x].l = l, tr[x].r = r, tr[x].lz = 0, tr[x].mul = 1;
    if(l==r){
        tr[x].sum = a[l]; return;
    }
    int mid = l+r>>1;
    build(ls(x),l,mid),build(rs(x),mid+1,r);
    psup(x);
    
}

// lazy tag 先乘后加

void use_lz(int x,int lz,int mul)
{
    Mod(tr[x].sum *= mul);
    Mod(tr[x].sum += (tr[x].r-tr[x].l+1)*lz);
    Mod(tr[x].mul *= mul);
    Mod(tr[x].lz *= mul);   
    Mod(tr[x].lz += lz);
}

void psdn(int x)
{
    use_lz(ls(x),tr[x].lz,tr[x].mul),use_lz(rs(x),tr[x].lz,tr[x].mul);
    tr[x].lz = 0,tr[x].mul = 1;
}

void add(int x,int l,int r,int L,int R,int k)
{
    if(L<=l && r<=R)
    {
        Mod(tr[x].sum += (r-l+1)*k);
        Mod(tr[x].lz += k);
        return;
    }
    psdn(x);
    int mid = l+r>>1;
    if(L<=mid) add(ls(x),l,mid,L,R,k);
    if(R>mid) add(rs(x),mid+1,r,L,R,k);
    psup(x);
}

void multy(int x,int l,int r,int L,int R,int k)
{
    if(L<=l && r<=R)
    {
        Mod(tr[x].sum *= k);
        Mod(tr[x].lz *= k);
        Mod(tr[x].mul *= k);
        return;
    }
    psdn(x);
    int mid = l+r>>1;
    if(L<=mid) multy(ls(x),l,mid,L,R,k);
    if(R>mid) multy(rs(x),mid+1,r,L,R,k);
    psup(x);
}

int qy(int x,int l,int r,int L,int R)
{
    if(L<=l&&r<=R) return tr[x].sum;
    int mid = l+r>>1;
    psdn(x);
    int res=0;
    if(L<=mid) Mod(res += qy(ls(x),l,mid,L,R));
    if(R>mid) Mod(res += qy(rs(x),mid+1,r,L,R));
    return res;
}

signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>mod;
    rep(i,1,n) cin>>a[i];
    build(1,1,n);
    rep(i,1,m)
    {
        int op,x,y,k;
        cin>>op>>x>>y;
        if(op==1) 
        {
            cin>>k;
            multy(1,1,n,x,y,k);
        }
        else if(op==2)
        {
            cin>>k;
            add(1,1,n,x,y,k);
        }
        else cout<<qy(1,1,n,x,y)<<'\n';

    }
    return 0;
}   