#include<bits/stdc++.h>

using namespace std;


int main()
{
	string str; cin>>str;
	int n; cin>>n;
	while(n--)
	{
		int op; cin>>op;
		if(op == 1)
		{
			cout<<str.size()<<'\n';
		}
		else 
		{
			string t; cin>>t;
			if(str.find(t) == string::npos) cout<<"-1\n";
			else cout<<str.find(t)<<'\n';
		}
	}

	return 0;
}