#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e5+10;
const int maxm=3e5+10;
int n,m,cnt;
LL ans,sum;
int fa[maxn][18],dep[maxn],head[maxn],maxx[maxn][18],minn[maxn][18];
bool used[maxn],vis[maxn];
struct Line
{
    int u,v,w;
    bool operator <(const Line&n1) const { return w<n1.w; }
}line[maxm];
struct Node
{
    int to,w,next;
}edge[maxm];

int findd(int x) { return x==fa[x][0]?x:fa[x][0]=findd(fa[x][0]); }

void add(int u,int v, int w) {
    edge[cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void kruskal() {
    for (int i=1;i<=n;i++) fa[i][0]=i;
    for (int i=1;i<=m;i++) {
        int a=findd(line[i].u),b=findd(line[i].v);
        if (a!=b) {
            fa[a][0]=b; sum+=line[i].w;
            add(line[i].u,line[i].v,line[i].w);
            add(line[i].v,line[i].u,line[i].w);
            used[i]=1;
        }
    }
}

void bfs() {
    memset(dep,0,sizeof(dep));
    memset(vis,0,sizeof(vis));
    fa[1][0]=0;
    queue<int> q;
    q.push(1);
    vis[1]=1;
    while (!q.empty()) {
        int u=q.front(); q.pop();
        for (int i=head[u];i!=-1;i=edge[i].next) {
            int v=edge[i].to;
            if (!vis[v]) {
                vis[v]=1;
                dep[v]=dep[u]+1;
                fa[v][0]=u;
                maxx[v][0]=edge[i].w;
                q.push(v);
            }
        }
    }
}

void pre_work() {
    for (int i=1;i<=17;i++)
        for (int j=1;j<=n;j++) {
            if (dep[j]>=(1<<i)) {
                fa[j][i]=fa[fa[j][i-1]][i-1];
                maxx[j][i]=max(maxx[j][i-1],maxx[fa[j][i-1]][i-1]);
                minn[j][i]=min(minn[j][i-1],minn[fa[j][i-1]][i-1]);
                if (maxx[j][i-1]>maxx[fa[j][i-1]][i-1] && maxx[fa[j][i-1]][i-1]>minn[j][i])
                    minn[j][i]=maxx[fa[j][i-1]][i-1];
                else if (maxx[j][i-1]<maxx[fa[j][i-1]][i-1] && maxx[j][i-1]>minn[j][i])
                    minn[j][i]=maxx[j][i-1];
            }
        }
}

int lca_get_value(int u,int v,int w) {
    if (dep[u]<dep[v]) swap(u,v);
    int l=u,r=v,mid=dep[u]-dep[v];
    int lca=0;
    for (int i=0; (1<<i)<=mid; i++)
        if ((1<<i)&mid) l=fa[l][i];
    if (l==r) lca=l;
    else {
        for (int i=17;i>=0;i--) {
            if (fa[l][i]!=fa[r][i]) {
                l=fa[l][i];
                r=fa[r][i];
            }
        }
        lca=fa[r][0];
    }
    l=u,r=v;
    int now=0;
    for (int i=17;i>=0;i--) {
        if (dep[l]-dep[lca]>=(1<<i)) {
            if (maxx[l][i]!=w) now=max(now,maxx[l][i]);
            else now=max(now,minn[l][i]);
            l=fa[l][i];
        }
        if (dep[r]-dep[lca]>=(1<<i)) {
            if (maxx[r][i]!=w) now=max(now,maxx[r][i]);
            else now=max(now,minn[r][i]);
            r=fa[r][i];
        }
    }
    return now;
}

void solve() {
    kruskal();
    bfs();
    pre_work();
    for (int i=1;i<=m;i++) {
        if (!used[i]) {
            LL tmp=lca_get_value(line[i].u,line[i].v,line[i].w);
            if (ans==0 && tmp!=line[i].w) ans=sum-tmp+line[i].w;
            if (tmp<line[i].w && ans>sum-tmp+line[i].w)
                ans=sum-tmp+line[i].w;
        }
    }
    printf("%lld\n", ans);
}

int main() {
    ans=0; cnt=0; sum=0;
    memset(used,0,sizeof(used));
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++) scanf("%d%d%d",&line[i].u,&line[i].v,&line[i].w);
    sort(line+1,line+1+m);
    solve();
    return 0;
}