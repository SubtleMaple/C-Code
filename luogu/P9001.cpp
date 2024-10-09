#include<iostream>
#define rep(i,a,n) for(int i=a;i<=n;++i)

using namespace std;

const int N = 1e5+7;

struct Que{
	int id,n,ans;
	Que(int id,int n,int ans):id(id),n(n),ans(ans){}
	
}que[N];

bool cmp1(Que a,Que b){
	return a.n < b.n;
}

bool cmp2(Que a,Que b){
	return a.id < b.id;
}

int main()
{
	int T;
	cin>>T;
	rep(i,1,T) {
		int x;cin>>x;
		que[i] = Que(i,x,0);
	}
	sort(que+1,que+T+1,cmp1);


	sort(que+1,que+T+1,cmp2);
	rep(i,1,T) 



	return 0;
}