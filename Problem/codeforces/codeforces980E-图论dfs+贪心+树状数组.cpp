// codeforces980E-图论dfs+树状数组
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
int n,k,tot;
vector<int> G[maxn];
int dep[maxn],f[maxn],in[maxn],out[maxn];
int a[maxn];
bool vis[maxn];
inline void add(int x,int num) {
    for (;x<=n;x+=x&(-x)) a[x]+=num;
}
inline int getsum(int x) {
    int r=0;
    for (;x;x-=x&(-x)) r+=a[x];
    return r;
}
inline void addseg(int l,int r,int num) {
    add(l,num); add(r+1,-num);
}

void dfs(int u,int fa) {
    in[u]=++tot; f[u]=fa; dep[u]=dep[fa]+1;
    int sz=G[u].size();
    for (int i=0;i<sz;i++) {
        int v=G[u][i];
        if (v==fa) continue;
        dfs(v,u);
    }
    out[u]=tot;
}
int main() {
    while (~scanf("%d%d",&n,&k)) {
        tot=0;
        for (int i=1;i<=n;i++) G[i].clear();
        memset(vis,0,sizeof(vis));
        memset(dep,0,sizeof(dep));
        memset(a,0,sizeof(a));
        int u,v;
        for (int i=0;i<n-1;i++) {
            scanf("%d%d",&u,&v);
            G[u].push_back(v); G[v].push_back(u);
        }
        dfs(n,n);
        vis[n]=1;
        addseg(in[n],out[n],1);
        k=n-k-1;
        for (int i=n-1;i>=1;i--) {
            if (vis[i]) continue;
            int tmp=dep[i]-getsum(in[i]);
            if (tmp>k) continue;
            for (int j=i;!vis[j];j=f[j]) {
                addseg(in[j],out[j],1);
                vis[j]=1;
                k--;
            }
        }
        for (int i=1;i<=n;i++) if (!vis[i]) printf("%d ", i);
        printf("\n");
    }
    return 0;
}