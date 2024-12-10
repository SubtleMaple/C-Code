#include<bits/stdc++.h>

using namespace std;

signed main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	string s,t;
	cin>>s>>t;
	int slen = s.size(), tlen = t.size();
	vector<int> pi(tlen,0);
	for(int i=1;i<tlen;++i)
	{
		int j = pi[i-1]; // now longest valid border length
		while(j && t[i] != t[j - 1 + 1]) j = pi[j-1]; // notice that pi[j-1], while j is a length but not an index
		if(t[i] == t[j - 1 + 1]) j++;
		pi[i] = j; 
	}

	// cerr<<"Yes\n";
	// for(int i=0;i<tlen;++i) cerr<<pi[i]<<' ';
	// cerr<<'\n';

	int j = 0;
	for(int i=0;i<slen;++i)
	{
		//cerr<<"I J: "<<i<<' '<<j<<'\n';
		while(j && s[i] != t[j - 1 + 1]) j = pi[j-1];
		if(s[i] == t[j - 1 + 1]) j++;
		if(j == tlen) {
			cout<<i+1-tlen+1<<'\n';
			j = pi[j-1]; // imagine there's a distinctive char at the tail of t
		}
	}
	for(int i=0;i<tlen;++i) cout<<pi[i]<<' ';
	return 0;
}