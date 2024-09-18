#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

void gmset(int x){
    if(!x) cout<<"Alice\n";
    else cout<<"Bob\n";
}

int main()
{   
    //若先手为0，则必败，若可重新排列中包含0，则必胜，否则必败；因为后手只需
    int T; cin>>T;
    while(T--)
    {
        int n;cin>>n;
        vector<int> a(n);
        rep(i,0,n-1) cin>>a[i];
        if(!a[0]){
            gmset(1);
        }
        else if(1)
        {
            rep(i,0,a[0]-1) if(!a[i]){
                gmset(0);
            }
        }
        else gmset(1);
        
    }

    return 0;
}