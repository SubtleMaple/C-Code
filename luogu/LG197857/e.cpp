//取模仅限于运算所需，对于此外一切需要维护的数据不可对原值取模    

#include<bits/stdc++.h>
#define lb(i) (i&-i)
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i)
using namespace std;

const int N = 1e6; 
const int mod = 998244353;

struct Que{
    int x,id,ans;
}que[N];

bool cmp1(Que x,Que y){
    return x.x < y.x;
}

bool cmp2(Que x,Que y){
    return x.id < y.id;
}

int n,q;
vector<int> cnt(N+2);

int ksm(int x,int t)
{
    int ans=1;
    while(t)
    {
        if(t&1){
            ans = (ans*x)%mod;
        }
        x = x*x%mod; t>>=1;
    }
    return ans;
}



signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>q;
    int d1=0,sum=0;
    int invn = ksm(n,mod-2);
    rep(i,1,n)
    {
        int l,r;
        cin>>l>>r;
        d1 += l*l;
        sum = sum+l; //需要的是真实的和，不可取模
        cnt[l+1]++,cnt[r+1]--;
    }
    rep(i,1,1000000) cnt[i] += cnt[i-1];
    rep(i,1,q) 
    {
        cin>>que[i].x;//注意之后程序需要比较x大小，所以不可对x取模，只有计算答案时才可对x取模
        que[i].id = i;
    }
    sort(que+1,que+q+1,cmp1);
    for(int i=1,j=0;i<=q;++i)
    {
        while(sum<que[i].x)
        {
            if(que[i].x-sum < cnt[j])
            {
                d1 = (d1 + (2*j-1)*(que[i].x-sum)%mod)%mod;
                cnt[j] -= que[i].x-sum;
                sum = que[i].x;
                break;
            }
            else
            {   
                d1 = (d1 + (2*j-1)*cnt[j]%mod)%mod;
                sum += cnt[j];
                //cnt[j] = 0;
                j++;
            }
        }
        que[i].x%=mod;
        que[i].ans = ((d1*invn%mod - que[i].x*que[i].x%mod*invn%mod*invn%mod)%mod+mod)%mod;
    }
    sort(que+1,que+q+1,cmp2);
    rep(i,1,q) cout<<que[i].ans<<'\n'; 
    return 0;
}