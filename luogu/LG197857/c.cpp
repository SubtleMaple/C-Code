        #include<bits/stdc++.h>

        using namespace std;

        int n;
        long long p;


        int main()
        {
            cin>>n>>p;
            for(int i=0;i<n;++i)
            {
                int x;cin>>x;
                if(x>0) p+=x;
            }
            cout<<p;
            return 0;
        }