#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define ll long long

const int N = 1e5+3;

int n;
ll a[N],mx[N<<2],sum[N<<2];

#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

void psup(int x)
{
    mx[x] = max(mx[ls(x)],mx[rs(x)]);
    sum[x] = sum[ls(x)] + sum[rs(x)];
}

void build(int x,int l,int r)
{
    sum[x] = 0;
    if(l==r){
        sum[x] = mx[x] = a[l]; return;
    }
    int mid = l+r>>1;
    build(ls(x),l,mid),build(rs(x),mid+1,r);
    psup(x);
}

void upd(int x,int l,int r,int L,int R)
{
    if(l==r)
    {
        sum[x] = mx[x] = sqrt(mx[x]);
        return;
    }
    int mid = l+r>>1;
    if(L <= mid && mx[ls(x)] > 1) upd(ls(x),l,mid,L,R);
    if(R > mid && mx[rs(x)] > 1) upd(rs(x),mid+1,r,L,R);
    psup(x);
}

ll qy(int x,int l,int r,int L,int R)
{
    if(L<=l && r<=R) return sum[x];
    int mid = l+r>>1; ll res=0;
    if(L<=mid) res += qy(ls(x),l,mid,L,R);
    if(R>mid) res += qy(rs(x),mid+1,r,L,R);
    return res;
}


int main()
{
    cin>>n;
    rep(i,1,n) cin>>a[i];
    build(1,1,n);
    int m; cin>>m;
    while(m--)
    {
        int k,l,r;
        cin>>k>>l>>r;
        if(!k)
        {
            upd(1,1,n,l,r);
        }
        else 
        {
            cout<<qy(1,1,n,l,r)<<'\n';  
        }
    }
    return 0;
}