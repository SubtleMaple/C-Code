#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)


int main()
{
    while(1)
    {
        string s;
        cin>>s;
        if(s=="-") break;
        int m; cin>>m;
        while(m--)
        {
            int h; cin>>h;
            string t = s;
            int len = s.size();
            for(int i = h; i < len; ++i) t[i-h] = s[i];
            for(int i=0;i<h;++i) t[len-h+i] = s[i];
            s = t;
        }
        cout<<s<<'\n';
    }

    return 0;
}