#include<iostream>

using namespace std;

const int N = 1e5+7;

int n,val[N],rt[N],dis[N],ch[N][2];
bool del[N];

int find(int x)
{
	return x == rt[x] ? x : rt[x] = find(rt[x]);
}

int merge(int x,int y)
{
	if(!x || !y) return x+y;
	if(val[x] > val[y]) swap(x,y);
	ch[x][1] = merge(ch[x][1],y);
	if(dis[ch[x][1]] > dis[ch[x][0]]) swap(ch[x][0],ch[x][1]);
	dis[x] = dis[ch[x][1]] + 1;
	return x;
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int m;
	cin>>n>>m;
	for(int i = 1; i <= n; ++i)
	{
		cin>>val[i];
		rt[i] = i;
	}
	while(m--)
	{
		int op; cin>>op;
		if(op == 1)
		{
			int x,y; cin>>x>>y;
			if(!del[x] && !del[y])
			{
				x = find(x);
				y = find(y);
				if(x != y) rt[x] = rt[y] = merge(rt[x],rt[y]);
			}
		}
		else
		{
			int x; cin>>x;
			if(del[x])
			{
				cout<<"-1\n";
				continue;
			}
			x = find(x);
			del[x] = 1;
			cout<<val[x]<<'\n';
			rt[x] = rt[ch[x][1]] = rt[ch[x][0]] = merge(ch[x][0],ch[x][1]);

		}
	}
	return 0;
}