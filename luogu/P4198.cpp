#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define db double

const int N = 1e5+7;

int n,m;
db a[N];

struct Tree{
    db mx; int len;
}tr[N<<2];

#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

int query(int x,int l,int r,db mx)
{
    if(l==r) return a[l] > mx;
    int mid = l+r>>1;
    if(tr[x].mx <= mx) return 0;
    if(tr[ls(x)].mx <= mx) return query(rs(x),mid+1,r,mx);

   // return query(ls(x),l,mid,mx) + query(rs(x),mid+1,r,tr[ls(x)].mx);
   // 由主定理知，上面注释的那一行时间复杂度 O(nlogn)
   // 优化：左右需要能连接起来，故需要找到右侧比左侧mx大的单增序列，而这个序列包含在tr[x].len中，
   // 只需减去左边部分 tr[ls(x)].len
   return query(ls(x),l,mid,mx) + tr[x].len - tr[ls(x)].len;
}

// int query(int x,int l,int r,db mx)
// {
//     if(l==r) return a[l] > mx;
//     int mid = l+r>>1;
//     if(tr[ls(x)].mx <= mx) return query(rs(x),mid+1,r,mx);
//     return query(ls(x),l,mid,mx) + tr[x].len - tr[ls(x)].len;
// }



void update(int p,int x,int l,int r,db w)
{
    if(l==r)
    {
        tr[x].mx = w, tr[x].len = 1;
        return;
    }
    int mid = l+r>>1;
    if(p<=mid) update(p,ls(x),l,mid,w);
    else update(p,rs(x),mid+1,r,w);
    tr[x].mx = max(tr[ls(x)].mx,tr[rs(x)].mx);
    tr[x].len = tr[ls(x)].len + query(rs(x),mid+1,r,tr[ls(x)].mx);
}



int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;

    rep(i,1,m)
    {
        int x,y; cin>>x>>y;
        a[x] = (db)y/x;
        update(x,1,1,n,a[x]);
        cout<<tr[1].len<<'\n';
    }
    return 0;
}