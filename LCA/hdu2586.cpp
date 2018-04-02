// LCA Tarjan
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
    int index;
} Q[MAXN];
int head[MAXN],headq[MAXN];
int lca[MAXN];
int fa[MAXN];
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

void addq(int u,int v,int w)
{
    Q[Qindex].index=w;
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
    memset(fa,-1,sizeof(fa));
    Eindex=Qindex=0;
}

int findd(int x)
{
    if (fa[x]==-1)
        return x;
    return fa[x]=findd(fa[x]);
}

void tarjan(int u)
{
    vis[u]=true;
    for (int i=head[u];i!=-1;i=E[i].next)
    {
        int v=E[i].v;
        int w=E[i].w;
        if (!vis[v])
        {
            dis[v]=dis[u]+w;
            tarjan(v);
            fa[v]=u;
        }
    }
    for (int i=headq[u];i!=-1;i=Q[i].next)
    {
        int v=Q[i].v;
        if (vis[v])
            lca[Q[i].index]=findd(v);
    }
}

int u,v,w;
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            _init();
            scanf("%d%d",&n,&m);
            for (int i=1;i<n;i++)
            {
                scanf("%d%d%d",&u,&v,&w);
                add(u,v,w);
                add(v,u,w);
            }
            for (int i=1;i<=m;i++)
            {
                scanf("%d%d",&u,&v);
                addq(u,v,i);
                addq(v,u,i);
            }

            dis[1]=0;
            tarjan(1);
            for (int i=0;i<Qindex;i+=2)
            {
                int len=dis[Q[i].u]+dis[Q[i].v]-2*dis[lca[Q[i].index]];
                printf("%d\n", len);
            }
        }
    }
    return 0;
}