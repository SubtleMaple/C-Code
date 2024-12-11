#include<bits/stdc++.h>

using namespace std;

const int N = 1e5+7;
int n,a[N],hpsize;

#define ls (x<<1)
#define rs (x<<1|1)

void update(int x)
{
	int mxid = x, mx = a[x];
	if(ls <= hpsize && a[ls] > mx) mxid = ls, mx = a[ls];
	if(rs <= hpsize && a[rs] > mx) mxid = rs, mx = a[rs];
	if(mxid != x)
	{
		swap(a[x], a[mxid]);
		update(mxid);
	}
}

void build()
{
	for(int i = n/2; i; i--)
	{
		update(i);
	}
}



int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n;
	hpsize = n;
	for(int i = 1; i <= n; ++i) cin>>a[i];
	build();
	for(int i = 1; i <= n; ++i)
	{
		cerr<<a[1]<<'\n';
		swap(a[1],a[hpsize]);
		hpsize--;
		update(1);
	}
	for(int i = 1; i <= n; ++i) cout<<a[i]<<' ';
	return 0;
}