#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

int a[101][101],b[101];

int main()
{
	int n,m;
	cin>>n>>m;
	rep(i,1,n) rep(j,1,m) cin>>a[i][j];
	rep(i,1,m) cin>>b[i];
	for(int i=1;i<=n;++i)
	{
		int res=0;
		for(int k=1;k<=m;++k) res += a[i][k] * b[k];
		cout<<res<<'\n';
	}

	return 0;
}