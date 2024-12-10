#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 7;

deque<int> q[27];

int n,s[N],cnt[26];
int t[N],rk[N];
bool vis[N];

#define lb(i) (i&-i)

void add(int x,int d){
	for(int i = x; i<= n; i += lb(i))
		t[i] += d;
}

int sum(int x){
	int res=0;
	for(int i=x; i; i -= lb(i))
		res += t[i];
	return res;
}

int main()
{
	string str;
	cin>>str;
	n = (int)str.size();
	for(int i=1;i<=n;++i){
		s[i] = (int)(str[i-1] - 'A');
		q[s[i]].push_back(i);
		cnt[s[i]]++;
	}
	int tmp=0; 
	for(int i=0;i<26;++i) if(cnt[i]&1){
		tmp++;
	}
	if(tmp>1){
		cout<<-1;return 0;
	}
	int tot=0,idx=0;
	while(tot < n/2){
		++idx;
		if(vis[idx]) continue;
		if((int)q[s[idx]].size() == 1) continue;
		rk[idx] = ++tot;
		vis[idx] = 1;
		rk[q[s[idx]].back()] = n - tot + 1;
		vis[q[s[idx]].back()] = 1;
		q[s[idx]].pop_front();
		q[s[idx]].pop_back();
	}
	for(int i=0;i<26;++i){
		if(!q[i].empty()) {
			rk[q[i].front()] = ++tot;
			break;
		}
	}
	int ans = 0;
	for(int i=1;i<=n;++i){
		add(rk[i],1);
		ans += i - sum(rk[i]);
	}
	cout<<ans;

	return 0;
}
