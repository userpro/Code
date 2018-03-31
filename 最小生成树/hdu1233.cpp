#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 100*(100-1)/2+10
struct Edge
{
    int u,v,c;
};
int N;
int F[MAXN];
Edge E[MAXN];

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
    while (scanf("%d",&N)==1&&N)
    {
        memset(F,-1,sizeof(F));
        int end=N*(N-1)/2;
        for (int i = 0; i < end; ++i)
            scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].c);
        sort(E,E+end,cmp);
        int ans=0;
        for (int i = 0; i < end; ++i)
        {
            int a=findd(E[i].u),b=findd(E[i].v);
            if (a!=b)
            {
                F[a]=b;
                ans+=E[i].c;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}