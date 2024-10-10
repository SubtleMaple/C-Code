#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)



void solv()
{
    int n,cnt=0,tp=0;
    cin>>n; 
    vector<int> stk(n+1);
    rep(i,1,n)
    {
        int x; cin>>x;
        while(tp && x < stk[tp]) tp--,cnt++;
        stk[++tp] = x;
    }
    if(stk[tp]!=n) cout<<-1;
    else cout<<cnt;


}

int main()
{
    solv();
    return 0;
}