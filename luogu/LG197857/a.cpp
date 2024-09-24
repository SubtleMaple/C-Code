#include<bits/stdc++.h>

using namespace std;

int main()
{
	vector<vector<int> > a(5);
	for(int i=0;i<5;++i) for(int j=0;j<5;++j) {
		int x; cin>>x; a[i].push_back(x);
	}
	int ans = 0;
	for(int i=0;i<5;++i)
	{
		int flg = 1;
		for(int j=0;j<5;++j) if(!a[i][j]) flg=0;
		ans |= flg;
		flg = 1;
		for(int j=0;j<5;++j) if(!a[j][i]) flg=0;
		ans |= flg;
	}
	int tmp=1;
	for(int i=0;i<5;++i)
	{
		if(!a[i][i]) tmp=0;
	}
	ans |= tmp;
	tmp = 1;
	for(int i=0;i<5;++i)
	{
		if(!a[i][4-i]) tmp=0;
	}
	ans |= tmp;
	cout<<(ans ? "Yes": "No");


	return 0;
}