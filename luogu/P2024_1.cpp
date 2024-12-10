#include<bits/stdc++.h>

using namespace std;


// 0 friend
// 1 eat
// 2 done

signed main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n,k,ans = 0; cin>>n>>k;

	//cerr<<n<<'\n';

	vector<int> dis(n+1,0),dsu(n+1,0);
	for(int i = 1; i <= n; ++i)  dsu[i] = i;

	//for(int i = 1; i <= n; ++i)  cerr<<dsu[i]<<'\n';

	function<int(int)> find = [&](int x)->int {
		//cerr<<"X DSU_X"<<x<<' '<<dsu[x]<<'\n';
		if(dsu[x] == x) return x;
		int g = find(dsu[x]);
		dis[x] += dis[dsu[x]];
		return dsu[x] = g;
	};

	while(k--)
	{
		//cerr<<"K: "<<k<<'\n';

		int op,x,y; cin>>op>>x>>y;
		if(x>n || y>n) {
			ans++; continue;
		}
		op--;
		int fx = find(x), fy = find(y);

		//cerr<<"K: "<<k<<'\n';

		if(fx == fy)
		{
			int d = ((dis[x] - dis[y])%3+3)%3; // vector plus
			if(d != op)
			{
				ans++;
			}
		}
		else
		{
			dsu[fx] = fy;
			// dsu 根节点的 dis 原本没有意义，dis 是个势能差
			dis[fx] = -dis[x] + op + dis[y];
			// x->y : t
			// y->fy : dis[y]
			// x->fx : dis[x]
			// fx->fy : lambda
			// fx->x->y->fy : lambda = -dis[x]+t+dis[y]
		}
	}
	cout<<ans;
	return 0;
}