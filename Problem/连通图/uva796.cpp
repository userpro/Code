// 当且仅当无向边（u, v）是树枝边的时候, 需要满足dfn(u)<low(v)
// 也就是v向上翻不到u及其以上的点, 那么u--v之间一定能够有1条或者多条边不能删去
// 因为他们之间有一部分无环, 是桥
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 10010
struct Edge
{
    int v,next;
} E[MAXN<<1];
struct Bridge
{
    int u,v;
    friend bool operator < (Bridge b1,Bridge b2)
    {
        if (b1.u==b2.u)
            return b1.v<b2.v;
        return b1.u<b2.u;
    }
} B[MAXN<<1];

int dfn[MAXN],low[MAXN];
int head[MAXN];
int fa[MAXN];
int Bindex,Eindex,n;

void _init()
{
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(head,-1,sizeof(head));
    memset(fa,0,sizeof(fa));
    Bindex=Eindex=0;
}

void add(int u,int v)
{
    E[Eindex].v=v;
    E[Eindex].next=head[u];
    head[u]=Eindex++;
    E[Eindex].v=u;
    E[Eindex].next=head[v];
    head[v]=Eindex++;
}

void Tarjan(int u,int f)
{
    fa[u]=f;
    dfn[u]=low[u]=++Bindex; // 写成Bindex++ WA
    for (int i=head[u];i!=-1;i=E[i].next)
    {
        int v=E[i].v;
        if (!dfn[v])
        {
            Tarjan(v,u);
            low[u]=min(low[u],low[v]);
        } else if (v!=f)
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
}

// 求桥
void solve()
{
    int ans=0;
    for (int i=0;i<n;i++)
        if (!dfn[i])
            Tarjan(i,-1);

    for (int i=0;i<n;i++)
    {
        int v=fa[i];
        if (v!=-1 && low[i]>dfn[v]) // 桥的条件
        {
            B[ans].v=v;
            B[ans].u=i;
            if (B[ans].u > B[ans].v)
                swap(B[ans].u,B[ans].v);
            ans++;
        }
    }
    sort(B,B+ans);
    printf("%d critical links\n", ans);
    for (int i=0;i<ans;i++)
        printf("%d - %d\n", B[i].u,B[i].v);
    printf("\n");
}

int main()
{
    int m,a,b;
    while (scanf("%d",&n)!=EOF)
    {
        _init();
        for (int i=0;i<n;i++)
        {
            scanf("%d (%d)",&a,&m);
            while (m--)
            {
                scanf("%d",&b);
                add(a,b);
            }
        }
        solve();
    }
    return 0;
}