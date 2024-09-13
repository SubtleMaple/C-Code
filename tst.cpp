#include<bits/stdc++.h>

#define lb(i) (i&-i)

using namespace std;

void work()
{
	vector<int> a = {1,2,3,4,5,6};
	auto it = lower_bound(a.begin(),a.end(),2);
	cout<<*it<<'\n';
	cout<< it - a.begin()<<'\n';

}

struct Node{
	int id,val;
};


signed main()
{
	Node a = {1,2};
	cout<< (&a)->id << a.val<<'\n';

	
	return 0;
}
