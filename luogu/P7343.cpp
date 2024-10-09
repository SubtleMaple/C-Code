    #include<bits/stdc++.h>
    using namespace std;
    #define rep(i,a,n) for(int i=a;i<=n;++i)

    const int N = 5e5+7;

    int n,m,a[N],r[N];

    int main()
    {
        cin>>n>>m;
        rep(i,1,n) cin>>a[i];
        rep(i,1,m) cin>>r[i];
        sort(r+1,r+m+1);
        r[0] = 0; r[m+1] = n;
        rep(i,1,m+1) sort(a+r[i-1]+1,a+r[i]+1);
        rep(i,1,n) cout<<a[i]<<' ';

        return 0;
    }