#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
int main()
{
    set<int> s;
    for(int i=10;i;i--) s.insert(i);
    for(auto x: s) cout<<x<<' ';
    return 0;
}