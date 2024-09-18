#include<iostream>
#include<cmath>
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define db double

using namespace std;

int a[4];

db f(db x)
{
    db tmp = 1.0,ans=0.0;
    rep(i,0,3)
    {
        ans += tmp*a[3-i];
        tmp *= x;
    }
    return ans;
}

bool ck(db x,db y)
{
    return f(x)*f(y) < 0;
}

int main()
{
    rep(i,0,3) scanf("%d",a+i);
    for(db x = -100.0;x<=100.0;x += 0.001) if(ck(x,x+0.001))
    {
        printf("%.2f ",x);
    }
    return 0;
}