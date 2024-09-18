#include<bits/stdc++.h>

using namespace std;

struct Node{
    int t,s;
}wk[1007];

int n,ans = 1e9+7;
bool cmp(Node x,Node y)
{
    return x.s > y.s;
}


int main()
{
    cin>>n;
    for(int i=1;i<=n;++i) cin>>wk[i].t>>wk[i].s;
    sort(wk+1,wk+n+1,cmp);
    ans = wk[1].s;
    for(int i=1;i<=n;++i)
    {
        ans = min(ans,wk[i].s);
        ans -= wk[i].t;
    }
    cout << max(-1,ans);
    return 0;
}