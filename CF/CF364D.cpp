#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

const int N = 1e6+7;

mt19937 rnd(time(0));

int n,tot;
ll a[N],num[N],cur,cnt[N],ans=1;

ll gcd(ll x,ll y) {
	return y==0 ? x : gcd(y,x%y);
}

void init() {
	rep(i,0,tot) num[i]=cnt[i]=0;
	tot=0;
}

void div() {
	for(ll x=1; x*x<=cur; ++x) {
		if(cur%x==0) {
			num[++tot] = x;
			if(x*x!=cur) num[++tot] = cur/x;
		}
	}
	sort(num+1,num+tot+1);
}

void solv() {
	rep(i,1,n) {
		ll ps = lower_bound(num+1,num+tot+1,gcd(a[i],cur))-num;
		cnt[ps]++;
	}
	rep(i,1,tot) {
		rep(j,i+1,tot) if(num[j]%num[i]==0) {
			cnt[i] += cnt[j];
		}
	}
	for(int i=tot; i; i--) if(cnt[i]*2 >= n) {
			ans = max(ans,num[i]);
			break;
		}
}

signed main() {
	// freopen("data.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	rep(i,1,n) cin>>a[i];
	rep(tm,1,10) {
		cur = a[rnd()%n+1];
		init();
		div();
		solv();
	}
	cout<<ans;
	return 0;
}
