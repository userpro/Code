#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1100
#define INF 1<<29
struct Edge
{
    char u,v;
    int c;
}edge[MAXN];
int N;
int F[MAXN];

bool cmp(Edge e1, Edge e2)
{
    return e1.c<e2.c;
}

int findd(int x)
{
    if (-1==F[x]) return x;
    return F[x]=findd(F[x]);
}

int main()
{
    char str1[5],str2[5];
    int num1,num2;
    while (scanf("%d",&N)==1&&N)
    {
        memset(F,-1,sizeof(F));
        for (int i = 0; i < MAXN; ++i)
        {
            edge[i].u=edge[i].v=0;
            edge[i].c=INF;
        }

        int t=0;
        for (int i = 0; i < N-1; ++i)
        {
            scanf("%s%d",str1,&num1);
            for (int j = 0; j < num1; ++j)
            {
                scanf("%s%d",str2,&num2);
                edge[t].u=str1[0]; edge[t].v=str2[0];
                edge[t].c=num2;
                t++;
            }
        }
        sort(edge,edge+t,cmp);

        int ans=0;
        for (int i = 0; i < t; ++i)
        {
            int a=findd(edge[i].u),b=findd(edge[i].v);
            if (a!=b)
            {
                F[a]=b;
                ans+=edge[i].c;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}