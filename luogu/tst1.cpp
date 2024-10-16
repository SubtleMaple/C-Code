#include<bits/stdc++.h>
#define int long long
#define ll long long
#define rop(i,a,n) for(ll i=a;i<n;++i)
#define rep(i,a,n) for(ll i=a;i<=n;++i)
using namespace std;

const int N = 100010;
const int INF = 1e13;
ll s;
int f[N], fa[N], nw[N], w[N], n;
vector<int> E[N]; int id;
int lim[N], b[N];
bool check(int u, int mid) {
	int m = E[u].size(); int s = 0;
	rop(i, 0, m) s += f[E[u][i]];
	if (s < mid) return 0;
	rop(i, 0, m) b[i] = max(0ll, 1ll*mid - lim[i]);
	s = 0; rop(i, 0, m) s += b[i];
	if (s > mid) return 0; return 1;
}
void dfs(int u) {
	int m = E[u].size();
	if (!m) { f[u] = INF; return; }
	for (auto v : E[u]) dfs(v);
	rop(i, 0, m) lim[i] = abs(nw[E[u][i]]);
	int mn = INF; rop(i, 0, m) mn = min(mn, f[E[u][i]] + lim[i]);
	int l = 0, r = mn;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (check(u, mid)) l = mid;
		else r = mid - 1;
	} f[u] = l;
}
void sub(int o) {
	cin>>n;
	rep(i, 1, n) f[i] = 0;
	rep(i, 2, n) cin>>fa[i];
	rep(i, 1, n) E[i].clear();
	rep(i, 1, n) E[fa[i]].push_back(i);
	rep(i, 1, n) cin>>w[i];
	rep(i, 1, n) nw[i] = w[i] - w[fa[i]];
	rep(i, 2, n) if (nw[i] > 0) {
		return puts("Shuiniao"), void();
	} dfs(1); 
	if (f[1] >= w[1]) puts("Huoyu");
	else puts("Shuiniao"); return;
}
signed main() {
    int T;
	cin>>id>>T;
	rep(o, 1, T) sub(o);
	return 0;
}