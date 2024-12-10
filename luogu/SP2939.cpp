// 维护树上任意点到特定点的最短路径，特定点可动态增加或减少


/*


lmn[x] = min(lmn[x],lmn[ls(x)]);

lmn[x] = min(lmn[x],siz[ls(x)] + min((col[x]==black)*inf,vdis[x]+1,lmn[rs(x)]+1));

//splay树是原树的一条链，更新链顶端的答案，用当前根的上方（左子树），当前根的下方（右子树，虚子树）分别更新

// 链最顶端到白点的距离，分为：在x上方更新（即x的左子树），在x更新， 以及在x的下方更新（x的虚子树或右子树）
// 其中 (col[x]==black) 为假时，x为白点，最上方距离x为 siz[ls(x)]
// 为真时x为黑点，在x的右子树和虚子树更新 (即 vdis[x] 或 lmn[rs(x)])
// lmn[rs(x)] 指向的是深度为 x+1 的点，即白点到x在原图链中的下一个点最近的距离
// vdis[x] 是白点到x的虚儿子最近的距离



rmn[x] = min(rmn[x],rmn[rs(x)]);

rmn[x] = min(rmn[x],siz[rs(x)] + min((col[x]==black)*inf,vdis[x]+1,rmn[ls(x)]+1));

rmn与lmn同理
*/
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

const int N = 1e5+7;
const int inf = 1e9;

int n;

int ch[N][2],fa[N],lzr[N];

int col[N],siz[N],lmn[N],rmn[N];

vector<int> G[N];
multiset<int> dis2[N];

#define vdis(x) (dis2[x].empty() ? inf : *dis2[x].begin())

#define ls(x) ch[x][0]
#define rs(x) ch[x][1]

bool isroot(int x){
    return ls(fa[x]) != x && rs(fa[x]) != x;
}

void psup(int x)
{
    siz[x] = 1 + siz[ls(x)] + siz[rs(x)];
    lmn[x] = min(lmn[ls(x)],siz[ls(x)]+min(col[x]*inf,min(lmn[rs(x)]+1,vdis(x))));
    rmn[x] = min(rmn[rs(x)],siz[rs(x)]+min(col[x]*inf,min(rmn[ls(x)]+1,vdis(x))));
}

void rotate(int x){
    int y = fa[x], z = fa[y];
    int k = ch[y][1] == x;
    if(!isroot(y)) ch[z][ch[z][1]==y] = x;
    fa[x] = z;
    ch[y][k] = ch[x][k^1];
    fa[ch[x][k^1]] = y;

    ch[x][k^1] = y;
    fa[y] = x;
    psup(y), psup(x);
}

void splay(int x){
    while(!isroot(x)){
        int y = fa[x], z = fa[y];
        if(!isroot(y))
            ((ls(z)==y)^(ls(y)==x)) ? rotate(x) : rotate(y);
        rotate(x);
    }
}

void access(int x){
    int z = x;
    for(int s = 0; x; s = x, x = fa[x])
    {
        splay(x);
        if(s) dis2[x].erase(dis2[x].find(lmn[s] + 1));
        if(rs(x)) dis2[x].insert(lmn[rs(x)] + 1); // multiset erase
        rs(x) = s;
        psup(x);
    }
    splay(z);
}

void dfs(int x,int fath)
{
    fa[x] = fath;
    for(auto v : G[x]) if(v != fath){
        dfs(v,x);
        dis2[x].insert(lmn[v] + 1);
    }
    psup(x);
}

int main()
{
    //freopen("data.in","r",stdin);
    ios::sync_with_stdio(0); cin.tie(0);
    lmn[0] = rmn[0] = inf;
    cin>>n;
    rep(i,1,n) col[i] = 1; //, lmn[i] = rmn[i] = inf;
    rep(i,1,n-1){
        int u,v; cin>>u>>v;
        G[u].push_back(v), G[v].push_back(u);
    }

    dfs(1,0);

    int q; cin>>q;
    while(q--){
        int op,v; cin>>op>>v;
        access(v);
        if(!op)
        {
            col[v] ^= 1;splay(v);
        }
        else
        {
            if(rmn[v] >= n) cout<<"-1\n";
            else cout<<rmn[v]<<'\n';
        }
       
    }
    return 0;
}