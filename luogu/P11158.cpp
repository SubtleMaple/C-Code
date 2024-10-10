#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define int long long
using namespace std;

const int N = 200007;

int n,m,a[N],ans;

set<int> s;

void calc()
{
	int l = *(s.begin()), r = *(s.rbegin());
	if(r - l + 1 == m) 
	{
		ans += m * (m - 1);
		ans += (l!=1) + (r!=n);
	}
	else
	{

		//注意：m == 2 时，次小值是最大值，次大值是最小值，而最小值和次大值是同一个数，两者的区间长度为1
		// if(m==2)
		// {
		// 	ans += 4;
		// 	ans -= (l==1) + (r==n);
		// 	return;
		// }
		int nl = *(next(s.begin())), pr = *(next(s.rbegin()));
		// 最小值到次大值连续，只有最大值游离
		if(pr - l + 1 == m - 1)
		{
			ans++; // 最大值放到次大值+1位置
			if(l != 1) ans++; //最大值放到最小值前
		}
		if(pr - l + 1 == m) ans++; // 最小值到次大值间只有一个空隙，将最大值补进去

		// 下面的情况与上面对称，同理即可
		if(r - nl + 1 == m - 1) 
		{
			ans++;
			if(r != n) ans++;
		}
		if(r - nl + 1 == m) ans++;

	}
}

void work()
{
	cin>>n;
	m = n/2;
	rep(i,1,n) cin>>a[i],s.insert(i);
	rep(i,1,m) s.erase(a[i]);
	calc();
	rep(i,1,m)
	{
		s.insert(a[i]);
		s.erase(a[i+m]);
		calc();
	}
	cout<<ans;
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
	work();
    return 0;
}