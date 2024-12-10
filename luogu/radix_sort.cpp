// 基数排序 P1177
// 小的先出桶，此为关键

#include<bits/stdc++.h>

using namespace std;

int get_bit(int x,int idx)
{
	idx--;
	while(idx--) x /= 10;
	return x % 10;
}

int main()
{
	vector<vector<int>> buc(10);
	int n; cin >> n;
	vector<int> cur(n);
	int mxbit = 0;
	for(int i = 1; i <= n; ++i)
	{
		int x; cin >> x;
		cur[i - 1] = x;
		int tmp = x, cnt = 0;
		while(tmp) cnt++, tmp /= 10;
		mxbit = max(mxbit,cnt);
	}
	for(int i = 1; i <= mxbit; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			buc[get_bit(cur[j],i)].push_back(cur[j]);
		}
		int timer = -1;
		for(int k = 0; k < 10; ++k)
		{
			for(int j = 0; j < buc[k].size(); ++j)
			{
				cur[++timer] = buc[k][j];
			}
			vector<int>().swap(buc[k]);
		}
	}
	for(int i = 0; i < n; ++i) cout << cur[i] << ' ';
	return 0;
}