#include<bits/stdc++.h>

using namespace std;

const int N = 6+7;
int n,a[N],hpsize;

#define ls (x<<1)
#define rs (x<<1|1)

void update(int x)
{
	int mnid = x, mn = a[x];
	if(ls <= hpsize && a[ls] < mn) mnid = ls, mn = a[ls];
	if(rs <= hpsize && a[rs] < mn) mnid = rs, mn = a[rs];
	if(mnid != x)
	{
		swap(a[x], a[mnid]);
		update(mnid);
	}
}

void push(int x)
{
	hpsize++;
	a[hpsize] = x;
	int now = hpsize;
	while(a[now] < a[now/2]) swap(a[now],a[now/2]),now /= 2;
}

void pop()
{
	swap(a[1],a[hpsize]);
	hpsize--;
	update(1);
}

void build()
{
	for(int i = n/2; i; i--)
	{
		update(i);
	}
}

int top()
{
	return a[1];
}


int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n;
	while(n--)
	{
		int op; cin>>op;
		if(op == 1)
		{
			int x; cin>>x;
			push(x);
		}
		else if(op == 2)
		{
			cout<<top()<<'\n';
		}
		else
		{
			pop();
		}
	}
	return 0;
}