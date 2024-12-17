#include<bits/stdc++.h>

using namespace std;

const int N = 1e5+7;

void solv()
{
	int n;
	while(cin>>n)
	{
		vector<int> dis(n+1),ls(n+1),rs(n+1),a(n+1),rt(n+1);
		for(int i = 1; i <= n; ++i)
		{
			cin>>a[i]; rt[i] = i;
		}

		function<int(int)> find = [&](int x){
			return x == rt[x] ? x : rt[x] = find(rt[x]);
		};

		function<int(int,int)> merge = [&](int x,int y){
			if(!x || !y) return x+y;
			if(a[x] < a[y]) swap(x,y);
			rs[x] = merge(rs[x],y);
			if(dis[rs[x]] > dis[ls[x]]) swap(ls[x],rs[x]);
			dis[x] = dis[rs[x]] + 1;
			return x;
		};
		auto change = [&](int x){
			a[x] >>= 1;
			int nrt = merge(ls[x],rs[x]);
			dis[x] = ls[x] = rs[x] = 0;
			rt[x] = rt[nrt] = merge(x,nrt);
		};

		int m; cin>>m;
		while(m--)
		{
			int x,y; cin>>x>>y;
			x = find(x), y = find(y);
			if(x == y)
			{
				cout<<"-1\n";
			}
			else
			{
				change(x), change(y);
				x = find(x), y = find(y);
				rt[x] = rt[y] = merge(x,y);
				cout<<a[rt[x]]<<'\n';
			}
		}
	}
}

int main()
{
	solv();
	return 0;
}