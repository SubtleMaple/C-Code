#include<bits/stdc++.h>

using namespace std;

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n,timer = 0; cin >> n;
	vector<vector<int>> tr;
	vector<int> cnt;
	tr.push_back(vector<int>(26,0));
	cnt.push_back(0);
	function<void(string&)> insrt = [&](string &s) -> void
	{
		int now = 0;
		for(int i = 0; s[i]; ++i)
		{
			int idx = s[i] - 'a';
			if(!tr[now][idx])
			{
				tr[now][idx] = ++timer;
				cnt.push_back(0);
				tr.push_back(vector<int>(26,0));
			}
			now = tr[now][idx];
		}
		cnt[now]++;
	};
	function<void(string&)> find = [&](string &s) -> void
	{
		int now = 0;
		for(int i = 0; s[i]; ++i)
		{
			int idx = s[i] - 'a';
			if(!tr[now][idx])
			{
				cout << "WRONG\n"; return;
			}
			now = tr[now][idx];
		}
		if(cnt[now] == 1){
			cout<< "OK\n"; cnt[now]++; return;
		}
		else if(!cnt[now]) {
			cout << "WRONG\n"; return;
		}
		else {
			cout << "REPEAT\n"; return;
		}
	};

	for(int i = 1; i <= n; ++i)
	{
		//cerr<<"Yes\n";
		string s; cin >> s; 
		insrt(s);
	}
	//cerr<<"Yes\n";
	int m; cin >> m;
	for(int i = 1;i <= m; ++i)
	{
		string t; cin >> t;
		find(t);
	}
	return 0;
}