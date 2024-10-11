#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

const int N = 103;

int n,m,in[N],cur[N];

int main()
{
    cin>>n;
    const int sn = n;
    vector<int> son[sn];
    rep(i,1,n)
    {
        int d;cin>>d;
        rep(j,1,d) {
            int x; cin>>x;
            son[x].push_back(i);
            in[i]++;
        }
    }
    cin>>m;
    while(m--)
    {
        int now=0;
        rep(i,1,n) cur[i]=0;
        rep(i,1,n)
        {
            int flg=1,x; cin>>x;
            flg = x & (cur[i]==in[i]);
            if(flg)
            {
                for(int j=0;j<(int)son[i].size();j++)
                {
                    cur[son[i][j]]++; 
                }
            }
            now += flg;
        }
        cout<<now<<'\n';
    }


    return 0;
}