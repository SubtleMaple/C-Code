#include<iostream>
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;

const int N = 50007;

int sum,n,m,dis[N];

bool ck(int mid) //min
{
    int now = 0,cnt=0;
    rep(i,1,n)
    {
        if(dis[i] - now >= mid) now = dis[i];
        else cnt++;
    }
    if(sum - now < mid) cnt++;
    return cnt <= m;
}

int main()
{
    freopen("data.in","r",stdin);
    cin>>sum>>n>>m;
    rep(i,1,n) cin>>dis[i];
    dis[n+1] = sum; // the last stone
    int l=1,r=sum+1;
    while(l<r-1)
    {
        int mid = (l+r)>>1;
        if(ck(mid)) l = mid;
        else r = mid;
    }
    cout<<l;

    return 0;
}