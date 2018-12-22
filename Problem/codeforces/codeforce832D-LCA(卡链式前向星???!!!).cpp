// codeforce832D-LCA(卡链式前向星???!!!)
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
int n,q;
vector<int> G[maxn];
int dep[maxn],f[maxn][25];
void dfs(int u,int fa) {
    dep[u]=dep[fa]+1;
    f[u][0]=fa;
    for (int i=0;i<=20;i++) f[u][i+1]=f[f[u][i]][i];
    int sz=G[u].size();
    for (int i=0;i<sz;i++) {
        int v=G[u][i];
        if (v==fa) continue;
        f[v][0]=u;
        dfs(v,u);
    }
}
inline int lca(int a,int b) {
    if (dep[a]<dep[b]) swap(a,b);
    for (int i=20;i>=0;i--) {
        if (dep[f[a][i]]>=dep[b]) a=f[a][i];
        if (a==b) return a;
    }
    for (int i=20;i>=0;i--) {
        if (f[a][i]!=f[b][i]) {
            a=f[a][i];
            b=f[b][i];
        }
    }
    return f[a][0];
}
inline int dis(int a,int b) { return dep[a]+dep[b]-2*dep[lca(a,b)]; }
int main() {
    while (~scanf("%d%d",&n,&q)) {
        for (int i=1;i<=n;i++) G[i].clear();
        int x;
        for (int i=2;i<=n;i++) {
            scanf("%d",&x);
            G[i].push_back(x);
            G[x].push_back(i);
        }
        dfs(1,0);
        int a,b,c;
        for (int i=1;i<=q;i++) {
            scanf("%d%d%d",&a,&b,&c);
            int t1=dis(a,b), t2=dis(a,c), t3=dis(b,c);
            int l1=(t1+t2-t3)/2+1;
            int l2=(t1+t3-t2)/2+1;
            int l3=(t2+t3-t1)/2+1;
            printf("%d\n", max(l1,max(l2,l3)));
        }
    }
    return 0;
}

/*
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
int n,q;
struct Edge
{
    int v,nx;
}e[maxn<<1];
int cnt,head[maxn],dep[maxn],f[maxn][25];
void _init() {
    cnt=0; memset(head,-1,sizeof(head));
}
inline void add(int u,int v) {
    e[cnt].v=v; e[cnt].nx=head[u]; head[u]=cnt++;
    e[cnt].v=u; e[cnt].nx=head[v]; head[v]=cnt++;
}
void dfs(int u,int fa) {
    dep[u]=dep[fa]+1;
    f[u][0]=fa;
    for (int i=0;i<=20;i++) f[u][i+1]=f[f[u][i]][i];
    for (int i=head[u];i!=-1;i=e[i].nx) {
        int v=e[i].v;
        if (v==fa) continue;
        f[v][0]=u;
        dfs(v,u);
    }
}
inline int lca(int a,int b) {
    if (dep[a]<dep[b]) swap(a,b);
    for (int i=20;i>=0;i--) {
        if (dep[f[a][i]]>=dep[b]) a=f[a][i];
        if (a==b) return a;
    }
    for (int i=20;i>=0;i--) {
        if (f[a][i]!=f[b][i]) {
            a=f[a][i];
            b=f[b][i];
        }
    }
    return f[a][0];
}
inline int dis(int a,int b) { return dep[a]+dep[b]-2*dep[lca(a,b)]; }
int main() {
    while (~scanf("%d%d",&n,&q)) {
        _init();
        int x;
        for (int i=2;i<=n;i++) {
            scanf("%d",&x);
            add(x,i); add(i,x);
        }
        dfs(1,0);
        int a,b,c;
        for (int i=1;i<=q;i++) {
            scanf("%d%d%d",&a,&b,&c);
            int t1=dis(a,b), t2=dis(a,c), t3=dis(b,c);
            int l1=(t1+t2-t3)/2+1;
            int l2=(t1+t3-t2)/2+1;
            int l3=(t2+t3-t1)/2+1;
            printf("%d\n", max(l1,max(l2,l3)));
        }
    }
    return 0;
}
*/