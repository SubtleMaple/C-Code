#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;


int n,f[51][51];
string str;

signed main()
{
	#ifdef LOCAL
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	#endif
	cin>>str;
	n = str.size();
	str = "$"+str; 
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;++i) f[i][i] = 1;
	for(int len = 2;len<=n;++len)
	{
		for(int i=1;i+len-1<=n;++i)
		{
			int j = i+len-1;
			if(str[i]==str[j])
			{
				f[i][j] = min(f[i][j-1],f[i+1][j]);
			}
			int mn = 0x3f3f3f3f;
			for(int k=i;k+1<=j;++k)
			{
				mn = min(mn,f[i][k]+f[k+1][j]);
			}
			f[i][j] = min(f[i][j],mn);
		}
	}
	cout<<f[1][n];




	return 0;
}

