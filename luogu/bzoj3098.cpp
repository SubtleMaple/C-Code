#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

int main()
{
    int n = 100000;
    cout<<n<<' '<<10<<'\n';
    rep(i,1,n) cout<<(rand()%26+'a');
    return 0;
}