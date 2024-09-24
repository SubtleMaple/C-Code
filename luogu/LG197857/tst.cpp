#include<bits/stdc++.h>
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;


int gcd(int x,int y)
{
    return y==0 ? x : gcd(y,x%y);
}

int lcm(int x,int y){
    return x/gcd(x,y)*y;
}



signed main()
{
    rep(i,1,100) rep(j,i,100) rep(k,1,100) rep(q,k,100) if(gcd(gcd(gcd(i,j),k),q)==1)
    {
        if(i+j+k+q == gcd(i,j) + lcm(k,q))
        {
            cout<<j<<' '<<i<<' '<<k<<' '<<q<<'\n';
        }
    }
    
    return 0;
}