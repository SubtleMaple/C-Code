    #include<bits/stdc++.h>
    using namespace std;
    #define rep(i,a,n) for(int i=a;i<=n;++i)

    int main()
    {
        string s;
        unordered_map<char,int> mp;
        cin>>s;
        for(auto ch : s) 
        {
            mp[ch] = 1;
        }
        for(char ch = 'a';ch <= 'z';ch++) if(!mp[ch]){
            cout<<ch; return 0;
        }
        cout<<"None";
        return 0;
    }