#include<bits/stdc++.h>

using namespace std;

const int N = 1e6+7;

int n,m,a[N],rt[N],dis[N];
pair<int,int> v[N];
int ch[N][2];
bool del[N];

int find(int x)
{
	return x == rt[x] ? x : rt[x] = find(rt[x]);
}

int merge(int x,int y)
{
	if(!x || !y) return x + y;
	if(v[x] > v[y]) swap(x,y);
	ch[x][1] = merge(ch[x][1],y);
	if(dis[ch[x][1]] > dis[ch[x][0]]) swap(ch[x][0],ch[x][1]);
	dis[x] = dis[ch[x][1]] + 1;
	return x;
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n;

	for(int i = 1; i <= n; ++i)
	{
		cin>>a[i]; rt[i] = i;	
		v[i] = make_pair(a[i],i);
	}
	cin>>m;

	while(m--)
	{
		char op; cin>>op;
		if(op == 'M')
		{
			int x,y; cin>>x>>y;
			if(!del[x] && !del[y] && (x=find(x)) != (y=find(y))) 
				rt[x] = rt[y] = merge(rt[x],rt[y]);

		}
		else
		{
			int x; cin>>x;
			if(del[x]) cout<<"0\n";
			else
			{
				x = find(x);
				del[x] = 1;
				cout<<a[x]<<'\n';
				// 由于路径压缩，其他点可能rt指向x，所以rt[x]也需要更新
				rt[x] = rt[ch[x][0]] = rt[ch[x][1]] = merge(ch[x][0], ch[x][1]);
			}
		}
	}
	return 0;
}