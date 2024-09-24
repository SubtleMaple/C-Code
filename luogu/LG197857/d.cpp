#include<bits/stdc++.h>
#define lb(i) (i&-i)
#define int long long

using namespace std;



signed main()
{
    int T;cin>>T;
    while(T--)
    {
        int x;
        cin>>x;
        int k = lb(x);
        x/=k;
        int b = x, c = x+2,d = 2;
        cout<<b*k<<' '<<c*k<<' '<<d*k<<'\n';
        
    }
    
    return 0;
}