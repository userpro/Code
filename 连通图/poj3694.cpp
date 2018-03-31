// 先求出强连通分支, 缩点形成一个树, 如果加入线路的两点在同一分支中
// 那么这条线路就没什么用了, 直接输出cnt就可以了
// 如果这两点不在同一分支中, 那么就相当于向一根树中加入一条边
// 然后将从这两点到他们最近公共祖先的线路都去掉就是现在网络中的“桥”的数量
// 这题不限时间, LAC用最原始的方法都能过, 因为对LAC的两种求法都不太熟悉, 所以就用了最原始的方法。
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 100010
#define MAXM 200010
struct Edge
{
    int v, next;
} E[MAXM<<1];
int n,m,q,cnt;
int Eindex,Bindex;
int head[MAXN],fa[MAXN],DFN[MAXN],LOW[MAXN];
bool vis[MAXN],mark[MAXN];

void add(int u,int v)
{
    E[Eindex].v=v;
    E[Eindex].next=head[u];
    head[u]=Eindex++;

    E[Eindex].v=u;
    E[Eindex].next=head[v];
    head[v]=Eindex++;
}

void dfs(int u)
{
    vis[u]=1;
    DFN[u]=LOW[u]=++Bindex;
    for (int i=head[u];i!=-1;i=E[i].next)
    {
        int v=E[i].v;
        if (!vis[v])
        {
            fa[v]=u;
            dfs(v);
            LOW[u]=min(LOW[u],LOW[v]);
            if (LOW[v]>DFN[u]) // 桥
            {
                cnt++;
                mark[v]=true;
            }
        } else if (vis[v] && v!=fa[u])
        {
            LOW[u]=min(LOW[u],DFN[v]);
        }
    }
}

void lca(int x,int y)
{
    while (DFN[x]>DFN[y])
    {
        if (mark[x])
        {
            cnt--;
            mark[x]=false;
        }
        x=fa[x];
    }
    while (DFN[y]>DFN[x])
    {
        if (mark[y])
        {
            cnt--;
            mark[y]=false;
        }
        y=fa[y];
    }
    while (x!=y)
    {
        if (mark[x])
        {
            cnt--;
            mark[x]=false;
        }
        if (mark[y])
        {
            cnt--;
            mark[y]=false;
        }
        x=fa[x];
        y=fa[y];
    }
}

int a,b;
int main()
{
    int C=0;
    while (scanf("%d%d",&n,&m)!=EOF&&(n||m))
    {
        memset(head,-1,sizeof(head));
        memset(DFN,0,sizeof(DFN));
        memset(LOW,0,sizeof(LOW));
        memset(fa,-1,sizeof(fa));
        memset(vis,false,sizeof(vis));
        memset(mark,false,sizeof(mark));
        fa[1]=1;
        cnt=Eindex=Bindex=0;
        for (int i=1;i<=m;i++)
        {
            scanf("%d%d",&a,&b);
            add(a,b);
        }
        for (int i=1;i<=n;i++)
            if (!DFN[i])
                dfs(i);

        scanf("%d",&q);
        printf("Case %d:\n", ++C);
        for (int i=1;i<=q;i++)
        {
            scanf("%d%d",&a,&b);
            //两点是否在同一分支中
            if (LOW[a]==LOW[b])
            {
                printf("%d\n", cnt);
                continue;
            }
            //求公共最近祖先
            lca(a,b);
            printf("%d\n", cnt);
        }
        printf("\n");
    }
    return 0;
}

