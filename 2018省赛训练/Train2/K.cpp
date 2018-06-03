#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
#define LL long long
#define INF (((LL)1)<<61)
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 100110
int T,N,M;
int head[MAXN];
bool vis[MAXN];
int tot;
struct edge_t
{
    LL v,d,c;
    int next;
} edge[MAXN*2];

struct node
{
    LL u,d,c;
    node() { }
    node(int u,int d,int c) : u(u),d(d),c(c) { }
    friend bool operator < (const node& n1,const node& n2)
    {
        if (n1.d==n2.d)
            return n1.c>n2.c;
        return n1.d>n2.d;
    }
} dis[MAXN];

void addedge(int u,int v,int d,int c)
{
    edge[tot].d=d; edge[tot].c=c;
    edge[tot].v=v; edge[tot].next=head[u];
    head[u]=tot++;
}

void dijk()
{
    for (int i=0;i<N;i++)
    {
        dis[i].u=i;
        dis[i].c=dis[i].d=INF;
    }
    CLR(vis,0);
    vis[0]=1;
    dis[0].c=dis[0].d=0;
    priority_queue<node> que;
    que.push(dis[0]);
    while (!que.empty())
    {
        int u=que.top().u; que.pop();
        vis[u]=0;
        for (int i=head[u];i!=-1;i=edge[i].next)
        {
            int v=edge[i].v,d=edge[i].d,c=edge[i].c;
            if (dis[u].d+d<dis[v].d || (dis[u].d+d==dis[v].d && c<dis[v].c))
            {
                dis[v].d=dis[u].d+d;
                dis[v].c=c;
                if (!vis[v])
                {
                    que.push(dis[v]);
                    vis[v]=1;
                }
            }
        }
    }
}

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        tot=0;
        CLR(edge,0);
        CLR(head,-1);
        scanf("%d%d",&N,&M);
        int x,y,d,c;
        while (M--)
        {
            scanf("%d%d%d%d",&x,&y,&d,&c);
            addedge(x,y,d,c);
            addedge(y,x,d,c);
        }
        dijk();
        LL sum_c=0,sum_d=0;
        for (int i=1;i<N;i++)
        {
            sum_c+=dis[i].c;
            sum_d+=dis[i].d;
        }
        printf("%lld %lld\n", sum_d,sum_c);
    }
    return 0;
}