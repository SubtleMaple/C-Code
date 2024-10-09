#include<bits/stdc++.h>
#define int long long
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;

const int N = 1000000,M = 100000,mod = 998244353;

int T;
int prim[N+5],vis[N+5],cnt,f[N+5],inv[N+5],res=1,ans[N+5 	];

vector<int> v;

void upd(int x,int tm)
{
	while(x>1)
	{
		int tmp = prim[x];
		res = res * inv[f[tmp]+1]%mod;
		f[tmp] += tm;
		res = res * (f[tmp]+1) % mod;
		x /= tmp;
	}
}

void init()
{
	vis[1] = 1; 
	for(int i=2;i<=N;i++)
	{
		if(!vis[i]){
			prim[i] = i; v.push_back(i);
		}
		for(auto x : v)
		{
			if(i*x > N) break;
			vis[i*x] = 1;
			prim[i*x] = x;
			if(i%x==0) break;
		}
	}
	//rep(i,1,cnt) cout<<prim[i]<<' ';
	inv[0] = inv[1] = 1;
    for (int i = 2; i <= N; i++){//线性递推出逆元
        inv[i] = mod - (mod / i * inv[mod % i] % mod) % mod;
    }
    for(int i=1;i<=N;++i)
	{
		upd(i,2);

		ans[i] = res;

		upd(i,-1);

	}

}


signed main()
{
	init();
	
	cin>>T;
	rep(i,1,T) {
		int x;cin>>x;
		if(x==1) cout<<"inf\n";
		else cout<<ans[x-1]<<'\n';
	}
	return 0;
}
