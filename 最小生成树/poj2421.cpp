#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 10010
struct Edge
{
    int u,v,c;
}edge[MAXN];
int N,Q;
int F[MAXN];

int findd(int x)
{
    if (-1==F[x]) return x;
    return F[x]=findd(F[x]);
}

bool cmp(Edge e1,Edge e2)
{
    return e1.c<e2.c;
}

int main()
{
    memset(F,-1,sizeof(F));
    scanf("%d",&N);
    for (int i = 1; i <= N; ++i)
        edge[i].u=edge[i].v=edge[i].c=0;
    int inx=0,t;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            scanf("%d",&t);
            if (i<=j) continue;
            edge[inx].u=i; edge[inx].v=j; edge[inx].c=t;
            inx++;
        }
    }
    sort(edge, edge+inx, cmp);

    scanf("%d",&Q);
    int u,v;
    for (int i = 0; i < Q; ++i)
    {
        scanf("%d%d",&u,&v);
        int a=findd(u),b=findd(v);
        if (a!=b) F[a]=b;
    }

    int ans=0;
    for (int i = 0; i < inx; ++i)
    {
        int a=findd(edge[i].u),b=findd(edge[i].v);
        if (a!=b)
        {
            F[a]=b;
            ans+=edge[i].c;
        }
    }
    printf("%d\n", ans);
    return 0;
}