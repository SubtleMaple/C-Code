#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

char s[10003];

int main()
{
    s[1] = 'a';
    int n = 1;
    for(int i=1;i<=12;++i)
    {
        for(int j=1;j<=n;++j)
        {
            s[j+n] = s[j]=='a' ? 'b' : 'a';
        }
        n<<=1;
    }
    int len = n>>1;
    cout<<n+65<<' '<<len<<'\n';
    rep(i,1,n) cout<<s[i];
    rep(i,1,65) putchar('a');


    return 0;
}