#include<bits/stdc++.h>

using namespace std;

const int N = 30000;

int fa[N+1],dis[N+1],siz[N+1];

// fa 是当前结点所在并查集的根节点，dis是x到并查集根节点的距离
// 由于本题中树的结构都只有链，所以siz 是当前并查集的大小

int find(int x)
{
	if(x == fa[x]) return x;
	int g = find(fa[x]);
	dis[x] += dis[fa[x]]; // 注意加的是x当前父节点的值
	return fa[x] = g;
}

void solv()
{
	for(int i = 1; i <= N; ++i) fa[i] = i, dis[i] = 0, siz[i] = 1;
	int p; cin >> p;
	while(p--)
	{
		char ch; int x,y; cin>>ch>>x;
		int fx = find(x); // 询问答案时也要更新x的dis
		if(ch == 'M')
		{
			cin>>y;
			int fy = find(y);
			fa[fx] = fy;
			dis[fx] += siz[fy];
			siz[fy] += siz[fx];
			//siz[fx] = 0;
		}
		else cout<<dis[x]<<'\n';
	}
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	solv();


	return 0;
}