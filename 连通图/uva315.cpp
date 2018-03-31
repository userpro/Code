// 无向图 求割点
// 一个顶点u是割点，当且仅当满足(1)或(2)
// (1) u为树根，且u有多于一个子树。
// (2) u不为树根，且满足存在(u,v)为树枝边(或称 父子边，即u为v在搜索树中的父亲)，使得 dfn(u)<=low(v)。
// （也就是说 V 没办法绕过 u 点到达比 u dfn要小的点）
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 10010
struct Edge
{
    int v;
    int next;
} E[MAXN<<1];
int DFN[MAXN];///代表最先遍历到这个点的时间
int LOW[MAXN]; ///这个点所能到达之前最早的时间点
int head[MAXN];
int fa[MAXN];
int n,Eindex,Index,Top;

void add(int u,int v)
{
    E[Eindex].v=v;
    E[Eindex].next=head[u];
    head[u]=Eindex++;

    E[Eindex].v=u;
    E[Eindex].next=head[v];
    head[v]=Eindex++;
}

void tarjan(int u,int fat)
{
    fa[u]=fat;
    DFN[u]=LOW[u]=++Index;
    for (int i=head[u];i!=-1;i=E[i].next)
    {
        int v=E[i].v;
        if (!DFN[v])
        {
            tarjan(v,u);
            LOW[u]=min(LOW[u],LOW[v]);
        } else if (fat!=v) /*假如k是i的父亲的话，那么这就是无向边中的重边，有重边那么一定不是桥*/
        {
            LOW[u]=min(LOW[u],DFN[v]);
        }
    }
}

// 求割点
void solve()
{
    int rootson=0,ans=0;
    bool isCut[MAXN]={false};

    tarjan(1,0);

    for (int i=2;i<=n;i++)
    {
        int v=fa[i];
        if (v==1) // i的父亲是根节点
            rootson++;
        else if (DFN[v]<=LOW[i])   ///判断是否满足条件（2）
            isCut[v]=true;
    }

    for (int i=2;i<=n;i++)
        if (isCut[i])
            ans++;

    if (rootson>1) // 条件1
        ans++;
    printf("%d\n", ans);
}

int a,b;
char ch;
int main()
{
    while (scanf("%d",&n),n)
    {
        memset(DFN,0,sizeof(DFN));
        memset(LOW,0,sizeof(LOW));
        memset(head,-1,sizeof(head));
        memset(fa,0,sizeof(fa));
        Eindex=Index=0;
        while (scanf("%d",&a),a)
        {
            while (scanf("%d%c",&b,&ch),b)
            {
                add(a,b);
                if (ch=='\n')
                    break;
            }
        }
        solve();
    }
    return 0;
}