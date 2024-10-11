#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define ll long long

const int N = 1e5+7;

int n,m,a[N];

// lazy tag 是给子节点用的，不是给自己用的
struct Tree{
    ll sum;
    int lz,l,r;
}tr[N<<2];

#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

void psup(int x)
{
    tr[x].sum = tr[ls(x)].sum + tr[rs(x)].sum;
}

void build(int x,int l,int r)
{
    tr[x].l = l, tr[x].r = r, tr[x].lz = 0;
    if(l==r){
        tr[x].sum = a[l]; tr[x].lz = 0; return;
    }
    int mid = l+r>>1;
    build(ls(x),l,mid),build(rs(x),mid+1,r);
    psup(x);
    
}

void use_lz(int x,int lz)
{
    tr[x].sum += (tr[x].r-tr[x].l+1)*lz;
    tr[x].lz += lz;
}

void psdn(int x)
{
    use_lz(ls(x),tr[x].lz),use_lz(rs(x),tr[x].lz);
    tr[x].lz = 0;
}

void add(int x,int l,int r,int L,int R,int k)
{
    if(L<=l && r<=R)
    {
        tr[x].sum += (r-l+1)*k;
        tr[x].lz += k;
        return;
    }
    psdn(x);
    int mid = l+r>>1;
    if(L<=mid) add(ls(x),l,mid,L,R,k);
    if(R>mid) add(rs(x),mid+1,r,L,R,k);
    psup(x);
}

ll qy(int x,int l,int r,int L,int R)
{
    if(L<=l&&r<=R) return tr[x].sum;
    int mid = l+r>>1;
    psdn(x);
    ll res=0;
    if(L<=mid) res += qy(ls(x),l,mid,L,R);
    if(R>mid) res += qy(rs(x),mid+1,r,L,R);
    return res;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    rep(i,1,n) cin>>a[i];
    build(1,1,n);
    rep(i,1,m)
    {
        int op,x,y,k;
        cin>>op>>x>>y;
        if(op==1) 
        {
            cin>>k;
            add(1,1,n,x,y,k);
        }
        else cout<<qy(1,1,n,x,y)<<'\n';

    }

    return 0;
}   