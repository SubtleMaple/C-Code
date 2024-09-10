#include<iostream>
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;

const int N = 1e5+7;

int n,m,dir[N];

string nam[N];

int main()
{
    //freopen("data.in","r",stdin);
    cin>>n>>m;
    rep(i,1,n)
    {
        cin>>dir[i]>>nam[i];
    }
    int now = 1;
    rep(i,1,m)
    {
        int a,s; cin>>a>>s;
        int d = dir[now] ^ a;
        if(!d) now = ((now-s)%n+n)%n; // 注意 now = 0 时特判
        else now = (now+s)%n;
    }
    cout<<nam[now];


    return 0;
}