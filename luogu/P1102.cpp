// #include<bits/stdc++.h>
// using namespace std;
// #define rep(i,a,n) for(int i=a;i<=n;++i)
// #define ll long long

// const int N = 2e5+7;
// unordered_map<ll,int> a;

// int b[N];


// int main()
// {
//     int n,c;
//     cin>>n>>c;
//     rep(i,1,n)
//     {
//         cin>>b[i];
//         int x = b[i];
//         if(!a[x]) a[x] = 1;
//         else a[x]++;
//     }
//     ll ans=0;
//     rep(i,1,n) 
//     {
//         ans += a[b[i]+c];
//     }   
//     cout<<ans;
//     return 0;
// }
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define ll long long

const int N = 2e5+7;

const int mod = 1000003;
int b[N];

struct Node
{
    ll x; int cnt;
}a[mod];

int hsh(int x)
{
    return x%mod;
}

int find(int x)
{
    int p = hsh(x);
    while(a[p].x && a[p].x != x) p = hsh(++p);
    a[p].x = x;
    return p;
}


int main()
{
    int n,c;
    cin>>n>>c;
    rep(i,1,n)
    {
        cin>>b[i];
        a[find(b[i])].cnt++;
    }
    ll ans=0;
    rep(i,1,n)
    {
        ans += a[find(b[i]+c)].cnt;
    }   
    cout<<ans;
    return 0;
}