// bzoj 1912 树的直径
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
int n,k;
// s1 最长链  s2 次长链  直径=max{s1+s2}
int head[maxn],s1[maxn],s2[maxn]; 
struct Edge
{
    int v,w,nx;
}edge[maxn<<1];
int cnt,mx,dir;

void _init() {
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(s1,-1,sizeof(s1));
    memset(s2,-1,sizeof(s2));
}

inline void add(int u,int v) {
    edge[cnt].v=v;
    edge[cnt].w=1;
    edge[cnt].nx=head[u];
    head[u]=cnt++;
}

int dfs(int u,int fa) {
    int mx1=0,mx2=0;
    for (int i=head[u];i!=-1;i=edge[i].nx) {
        int v=edge[i].v;
        if (v==fa) continue;
        int t=dfs(v,u)+edge[i].w;
        if (mx1<t) mx2=mx1,mx1=t,s2[u]=s1[u],s1[u]=i;
        else if (mx2<t) s2[u]=i,mx2=t;
    }
    if (mx1+mx2>mx) mx=mx1+mx2, dir=u;
    return mx1;
}

int main() {
    _init();
    scanf("%d%d",&n,&k);
    int u,v;
    for (int i=1;i<n;i++) {
        scanf("%d%d",&u,&v);
        add(u,v); add(v,u);
    }
    int ans=0;
    dfs(1,0);
    ans=(n-1)*2-mx+1;
    if (k==2) {
        mx=0;
        for (int i=s1[dir];i!=-1;i=s1[edge[i].v]) edge[i].w=edge[i^1].w=-1;
        for (int i=s2[dir];i!=-1;i=s1[edge[i].v]) edge[i].w=edge[i^1].w=-1;
        dfs(1,0);
        ans=ans-mx+1;
    }
    printf("%d\n", ans);
    return 0;
}
