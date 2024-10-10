#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

const int N = 1e5+7;

int main()
{
    int n; cin>>n;
    vector<int> a(n);
    rep(i,0,n-1) cin>>a[i];
    for(int i=1;i<n;++i)
    {
        int ky = a[i];
        rep(j,0,i-1) if(a[j] > ky)
        {
            for(int q=i;q>j;q--) a[q] = a[q-1];
            a[j] = ky;
            break;
        }
    }
    rep(i,0,n-1) cout<<a[i]<<' ';
    return 0;
}