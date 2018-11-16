#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
int n,k;
int head[maxn],v[maxn],a[maxn],mark[maxn],L[maxn],R[maxn];
struct Edge
{
    int v,nx;
}edge[maxn<<1];
int cnt;
bool flag;

void _init() {
    cnt=0;
    memset(head,-1,sizeof(head));
}

void add(int u,int v) {
    edge[cnt].v=v; edge[cnt].nx=head[u];
    head[u]=cnt++;
    edge[cnt].v=u; edge[cnt].nx=head[v];
    head[v]=cnt++;
}

void dfs1(int u,int fa) {
    if (mark[u] && (v[u]^(a[u]&1))) {
        flag=0; return;
    }
    for (int i=head[u];i!=-1;i=edge[i].nx) {
        int to=edge[i].v;
        if (to==fa) continue;
        v[to]=v[u]^1;
        dfs1(to,u);
    }
}

void dfs2(int u,int fa) {
    if (mark[u]) L[u]=R[u]=a[u];
    else L[u]=-1e9,R[u]=1e9;
    for (int i=head[u];i!=-1;i=edge[i].nx) {
        int to=edge[i].v;
        if (to==fa) continue;
        dfs2(to,u);
        L[u]=max(L[to]-1,L[u]);
        R[u]=min(R[to]+1,R[u]);
    }
    if (L[u]>R[u]) flag=0;
}

void dfs3(int u,int fa) {
    for (int i=head[u];i!=-1;i=edge[i].nx) {
        int to=edge[i].v;
        if (to==fa) continue;
        a[to]=a[u]+(a[u]+1>R[to]?-1:1);
        dfs3(to,u);
    }
}

int main() {
    _init();
    flag=1;
    scanf("%d",&n);
    int x,y;
    for (int i=1;i<n;i++) {
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    scanf("%d",&k);
    for (int i=1;i<=k;i++) {
        scanf("%d%d",&x,&y);
        a[x]=y; mark[x]=1;
    }
    for (int i=1;i<=n;i++) {
        if (!mark[i]) continue;
        v[i]=a[i]&1; dfs1(i,i);
        break;
    }
    if (!flag) { puts("No"); return 0; }
    dfs2(1,1);
    if (!flag) { puts("No"); return 0; }
    L[1]+=((L[1]&1)^v[1]);
    a[1]=L[1];
    dfs3(1,1);
    puts("Yes");
    for (int i=1;i<=n;i++) printf("%d\n", a[i]);
    return 0;
}

