    #include<bits/stdc++.h>
    using namespace std;
    #define int long long
    #define rep(i,a,n) for(int i=a;i<=n;++i)

    signed main()
    {
        unordered_map<int,int> mp;
        int n;cin>>n;
        int lst = -1,ar = 0;
        rep(i,1,n)
        {
            int x; cin>>x;
            mp[x]++;
            if(mp[x] > 1)
            {
                if(lst != -1)
                {
                    ar = max(ar,lst*x);
                    if(lst < x)
                    {
                        mp[lst] += 2;
                        mp[x] -= 2;
                        lst = x;
                    }
                }
                else {
                    lst = x; mp[x] -= 2;
                }
            }
        }
        cout<<ar;
        return 0;
    }