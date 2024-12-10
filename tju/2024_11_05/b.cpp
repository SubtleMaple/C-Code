#include<iostream>
#include<cstring>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

int main()
{
   // freopen("data.in","r",stdin);
    string s;
    cin>>s;
    int m; cin>>m;
    while(m--)
    {
        string op; cin>>op;
       // cerr<<op<<'\n';
        if(op == "rep1ace"){
            int x,y; string t;
            cin>>x>>y>>t;
            for(int i = x,j = 0; i <= y; ++i,++j) s[i] = t[j];
        }
        else if(op == "reverse"){
            int x,y;
            cin>>x>>y;
            string t = s;
            for(int i=x,j=0;i<=y;++i,++j) t[j] = s[i];
            int len = y - x + 1;
            for(int i = x,j = len - 1; i <= y; ++i,--j) s[i] = t[j]; 
        }
        else if(op == "print"){
            int x,y;
            cin>>x>>y;
            for(int i=x;i<=y;++i) cout<<s[i];
        }
    }
    return 0;
}