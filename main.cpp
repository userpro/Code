#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
#define MAXN 40010
#define MAXM 210
struct Edge
{
    int v;
    int w;
    int next;
} E[MAXN<<1];
struct Question
{
    int u;
    int v;
    int next;
    int lca;
} Q[MAXN];
int head[MAXN],headq[MAXN];
int fa[MAXN],anc[MAXM];
int dis[MAXN];
bool vis[MAXN];
int Eindex,Qindex;
int T,n,m;

void add(int u,int v,int w)
{
    E[Eindex].v=v;
    E[Eindex].w=w;
    E[Eindex].next=head[u];
    head[u]=Eindex++;
}

void addq(int u,int v)
{
    Q[Qindex].lca=0;
    Q[Qindex].v=v;
    Q[Qindex].u=u;
    Q[Qindex].next=headq[u];
    headq[u]=Qindex++;
}

void _init()
{
    memset(head,-1,sizeof(head));
    memset(headq,-1,sizeof(headq));
    memset(vis,false,sizeof(vis));
    memset(dis,0,sizeof(dis));
    Eindex=Qindex=0;
}

int findd(int x)
{
    if (fa[x]==x)
        return x;
    return fa[x]=findd(fa[x]);
}

void unionn(int x,int y)
{
    x=findd(x);
    y=findd(y);
    if (x!=y)
        fa[x]=y;    
}

void tarjan(int u)
{
    vis[u]=true;
    anc[u]=fa[u]=u;
    for (int i=head[u];i!=-1;i=E[i].next)
    {
        int v=E[i].v;
        int w=E[i].w;
        if (!vis[v])
        {
            dis[v]=dis[u]+w;
            tarjan(v);
            unionn(u,v);
            anc[findd(u)]=u;
        }
    }
    for (int i=headq[u];i!=-1;i=Q[i].next)
        if (vis[Q[i].v])
            Q[i].lca=anc[findd(Q[i].v)];
}

int a,b,w;
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        _init();
        scanf("%d%d",&n,&m);
        for (int i=1;i<n;i++)
        {
            scanf("%d%d%d",&a,&b,&w);
            add(a,b,w);
            add(b,a,w);
        }
        for (int i=1;i<=m;i++)
        {
            scanf("%d%d",&a,&b);
            addq(a,b);
        }
        tarjan(1);
        for (int i=1;i<=m;i++)
        {
            printf("%d\n", E[Q[i].lca].w);
            // int u=Q[i].u,v=Q[i].v,lca=Q[i].lca;
            // printf("%d\n", dis[u]+dis[v]-2*dis[lca]);
        }
    }
    return 0;
}