#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

vector<pair<int,int> > v;

int main()
{
    int n,k,res=0,num=0;
    cin>>n>>k;
    int tmp = n;
    for(int i=2;i*i<=n;++i)
    {
        if(tmp%i) continue;
        int tot=0;
        while(tmp%i==0) tmp/=i,tot++;
        res += i*tot;
        v.push_back({i,tot});
        num += tot;
    }
    if(tmp != 1){
        res += tmp;
        v.push_back({tmp,1});
        num++;
    }
    if(res > k)
    {
        cout<<-1; return 0;
    }
    int a = k - res;
    cout<<num + a<<'\n';
    for(auto i : v)
    {
        for(int j = 1; j <= i.second; ++j) cout<<i.first<<' ';
    }
    for(int i=1;i<=a;++i) cout<<1<<' ';

    return 0;
}