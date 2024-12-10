// 负环
#include<bits/stdc++.h>

using namespace std;

struct EDGE{
	int to,nxt,val;
};

void solv()
{
	int n,m,qcnt=0; cin >> n >> m;
	vector<int> h(n+1);
	vector<EDGE> e(2*m+1);

	auto addedge = [&](int u,int v,int w) -> void{
		e[++qcnt] = (EDGE){v,h[u],w};
		h[u] = qcnt;
	};

	for(int i = 1; i <= m; ++i)
	{
		int u,v,w; cin >> u >> v >> w;
		addedge(u,v,w);
		if(w >= 0) addedge(v,u,w);
	}

	queue<int> q;
	vector<bool> vis(n+1);
	vector<int> dis(n+1,(int)1e9);
	vector<int> cnt(n+1);
	dis[1] = 0;
	q.push(1); vis[1] = 1; cnt[1]++;
	while(!q.empty())
	{
		int u = q.front(); q.pop(); vis[u] = 0;
		for(int i = h[u]; i; i = e[i].nxt)
		{
			int v = e[i].to;
			//if(vis[v]) continue;
			if(dis[v] > dis[u] + e[i].val)
			{
				dis[v] = dis[u] + e[i].val;
				if(!vis[v]) {
					cnt[v]++;
					if(cnt[v] >= n)	{
						cout<<"YES\n"; return;
					}
					q.push(v); vis[v] = 1;
				}
			}
		}
	}
	cout<<"NO\n";

}

int main()
{
	int tt; cin>>tt;
	while(tt--) solv();
	return 0;
}