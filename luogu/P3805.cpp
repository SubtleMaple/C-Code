// manacher's algorithm

#include<bits/stdc++.h>

using namespace std;

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int ans=0;
	string ss=""; cin>>ss;
	int len = ss.size();
	len = 2 * len + 1;
	string s = "$";
	vector<int> rc(len+1);

	for(int i=0;i<ss.size();++i)
	{
		if(!i) s += "#"; 
		s += ss[i]; s += "#";
	}
	int c=0,r=0;
	for(int i=1;i<=len;++i)
	{
		if(i>r) // case 1
		{
			int j = i;
			while(s[j+1] == s[2*i-j-1]) j++;
			rc[i] = j - i;
		}
		else
		{
			int ii = 2*c-i;
			int il = ii - rc[ii];
			int l = 2*c-r;
			if(l < il) // case2
			{ 
				rc[i] = rc[ii];
			}
			else if(il < l) // case3
			{
				rc[i] = r - i;
			}
			else if(il == l) // case4
			{
				rc[i] = rc[ii];
				int j = i + rc[i];
				while(s[j+1] == s[2*i-j-1]) j++;
				rc[i] = j - i;
			}
		}
		ans = max(ans,rc[i]);
		if(rc[i] + i > r) {
			c = i, r = rc[i] + i;
		}
	}
	cout<<ans<<'\n';
	return 0;
}