// poj1741 求树中两个节点d[x]+d[y]<k有多少个 点分治
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf=1<<29;
const int maxn=1e4+10;
int n,k;
int head[maxn],size[maxn],dis[maxn],mxson[maxn];
bool vis[maxn];
struct Edge
{
    int to,w,next;
}edge[maxn<<1];
int cnt,tot,root,sum; // sum 子树大小

void _init() {
    cnt=tot=root=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
}

inline void add(int u,int v,int w) {
    edge[cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

inline void dfs_root(int u,int f) {
    mxson[u]=0;
    size[u]=1;
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (vis[v]||v==f) continue;
        dfs_root(v,u);
        size[u]+=size[v];
        mxson[u]=max(mxson[u],size[v]);
    }
    mxson[u]=max(mxson[u],sum-size[u]); // sum-size[u] !!!
    if (mxson[u]<mxson[0]) {
        mxson[0]=mxson[u];
        root=u;
    }
}

inline void dfs_dis(int u,int f,int dist) {
    dis[++tot]=dist;
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (vis[v]||v==f) continue;
        dfs_dis(v,u,dist+edge[i].w);
    }
}

inline int calc(int u,int dist) {
    tot=0;
    dfs_dis(u,u,dist);
    sort(dis+1,dis+1+tot);
    int res=0;
    int i=1,j=tot;
    for (int i=1;i<j;i++) {
        while (dis[i]+dis[j]>k&&i<j) j--;
        res+=(j-i);
    }
    return res;
}

inline int dfs(int u) {
    mxson[0]=inf;
    dfs_root(u,u);
    vis[root]=1;
    int res=calc(root,0);
    for (int i=head[root];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (vis[v]) continue;
        res-=calc(v,edge[i].w);
        sum=size[v];
        res+=dfs(v);
    }
    return res;
}

int main() {
    while (scanf("%d%d",&n,&k)!=EOF && (n||k)) {
        _init();
        int u,v,w;
        for (int i=1;i<n;i++) {
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w); add(v,u,w);
        }
        sum=n;
        printf("%d\n", dfs(1));
    }
    return 0;
}

