#include<bits/stdc++.h>
#define int long long
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

void mul(int *a,int *b)
{
    int res[1007];
    memset(res,0,sizeof(res));
    rep(i,1,500) rep(j,1,500)
    {
        res[i+j-1] += a[i]*b[j];
        res[i+j] += res[i+j-1]/10;
        res[i+j-1] %= 10;
    }
    rep(i,1,500) a[i] = res[i];
}

void ksm(int tm)
{
    int res[503],tmp[503],b[503];
    memset(res,0,sizeof(res));
    memset(tmp,0,sizeof(tmp));
    res[1] = 1; tmp[1] = 2;
    while(tm)
    {
        if(tm&1){
            mul(res,tmp);
        }
        rep(i,1,500) b[i]=tmp[i];
        mul(tmp,b); tm>>=1;
    }
    res[1]--;
    for(int i=500,j=0;i;i--)
    {
        cout<<res[i]; j++;
        if(j==50){
            puts("");j=0;
        }
    }
}

signed main()
{
    int p;
    cin>>p;
    int bit = p*log10(2)+1;
    cout<<bit<<'\n';
    ksm(p);  
    return 0;
}