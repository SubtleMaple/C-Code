#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n,m,e; cin>>n>>m>>e;
	vector<vector<int>> G(n+1,vector<int>());
	vector<int> vis(m+1);
	vector<int> mat(m+1);
	for(int i=1;i<=e;++i)
	{
		int u,v; cin>>u>>v;
		G[u].push_back(v);
	}

	function<bool(int)> match = [&](int x)->bool{
		for(auto y : G[x])
		{
			if(vis[y]) continue; // 每次重置为0，防止成环
			vis[y] = 1;
			if(!mat[y] || match(mat[y])) {
				mat[y] = x;
				return 1;
			}
		}
		return 0;
	};
	int ans=0;
	for(int i=1;i<=n;++i) {
		ans += match(i);
		fill(vis.begin(),vis.end(),0);
	}
	cout<<ans;
	return 0;
}