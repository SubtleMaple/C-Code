// 注意题目要求：A吃B，B吃C，C吃A

// 所有动物都只属于 ABC
// 所以每两个动物的关系是唯一确定的
// 即x若吃y，x和y既不可能是同类，y也不可能吃x
// 下面考虑 A1吃B2，和 B1吃C2 的关系：
// 由于 A1和B1无关，B2与C2无关，所以如果同时令二者成立，
// 那么二者与其他动物的关系不受它们同时成立的影响


#include<bits/stdc++.h>

using namespace  std;

// x itself
// x + n x eat
// x + 2 * n x be eaten

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n,k;
	cin>>n>>k;
	vector<int> dsu(3*n+1);
	for(int i = 1; i <= 3*n; ++i) dsu[i] = i;

	function<int(int)> find = [&](int x)->int{
		return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
	};

	auto connect = [&](int x,int y)->void{
		dsu[find(x)] = find(y);
	};

	int false_cnt = 0;
	while(k--)
	{
		int op,x,y;
		cin>>op>>x>>y;
		if(x > n || y > n) {
			false_cnt++; continue;
		}
		if(op == 1)
		{
			if(find(x) == find(y+n) || find(x+n) == find(y))
			{
				false_cnt++; continue;
			}
			else
			{
				connect(x,y);
				connect(x+n,y+n);
				connect(x+n+n,y+n+n);
			}
		}
		else
		{
			if(find(x)==find(y) || find(y)==find(x+n))
			{
				false_cnt++; continue;
			}
			else
			{
				connect(x,y+n);
				connect(x+n,y+n+n);
				connect(x+n+n,y);
			}
		}
	}
	cout<<false_cnt;
	return 0;
}
// 1->2
// A1->B2, B1->C2, C1->A2
// 2->3
// A2->B3, B2->C3, C2->A3

// 得到： A1,B2,C3; B1,C2,A3; C1,A2,B3

// 相同数字的不同字母若在同一个并查集中，则说明他吃自己

// 在同一个并查集中，则其中的ABC一定满足题意的捕食关系