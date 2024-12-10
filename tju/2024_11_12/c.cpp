#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

bool ck(int x)
{
    string s = "0";
    int cnt=0;
    while(x)
    {
        cnt++;
        s += (char)(x%10 + '0');
        x /= 10;
    }
    int ad = 1 + cnt;
    bool flg = 1;
    for(int i=1;i<=cnt;++i) if(s[i] != s[ad - i]) flg = 0;
    return flg;
}

int main()
{
    for(int i=11;i<=999;++i)
    {
        if(ck(i) && ck(i*i) && ck(i*i*i))
            cout<<i<<'\n';
    }
    return 0;
}