#include<bits/stdc++.h>

using namespace std;

const string ans = "rioi";

bool ck(const string &s)
{
	for(int i=0; i < (int)s.size()-3;++i)
	{
		string subs = s.substr(i,4);
		if(subs == ans) return 1;
	}
	return 0;
}

int main()
{
	string s,t;
	cin>>s>>t;
	string S = s, T = t;
	transform(s.begin(),s.end(),s.begin(),::tolower);
	transform(t.begin(),t.end(),t.begin(),::tolower);
	int flg1 = ck(s),flg2 = ck(t);
	if(flg1&&flg2) cout<<"Either is ok!\n";
	else if(flg1) cout<<S<<" for sure!";
	else if(flg2) cout<<T<<" for sure!";
	else cout<<"Try again!\n";
	
	
	return 0;
}