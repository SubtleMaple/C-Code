#include<bits/stdc++.h>
#define int long long
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
const int mod = 1000000007;

void Mod(int &x){
    x%=mod;
}

signed main()
{
    string s[3];
    int n;
    cin>>n;
    cin>>s[1]>>s[2];
    int i=0,ans=1,lst=-1;
    while(i<n)
    {
        if(i==0)
        {
            if(s[1][i] != s[2][i])//2
            {
                Mod(ans*=6); lst = 2;
            }
            else//1
            {
                Mod(ans*=3); lst = 1;
            }
            i+=lst;
        }
        else  
        {
            if(s[1][i] != s[2][i])//2
            {
                if(lst==2) Mod(ans*=3); // 2 2
                else Mod(ans*=2); // 1 2
                lst = 2;
            }
            else//1
            {
                if(lst==1) Mod(ans*=2); // 1 1
                lst = 1; 
            }
            i+=lst;
        }
    }
    cout<<ans;
    
    return 0;
}