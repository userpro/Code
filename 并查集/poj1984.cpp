#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
#define MAXN 40010
struct Node
{
    int u,v,i,inx;
}node[MAXN];
int N, M, K;
int F[MAXN];
int dx[MAXN], dy[MAXN];
int F1[MAXN], F2[MAXN], L[MAXN];
int ans[MAXN];
char D[MAXN][3];

bool cmp(Node a, Node b)
{
    return a.i < b.i;
}

int findd(int x)
{
    if (-1==F[x]) return x;
    int t = findd(F[x]);
    dx[x]+=dx[F[x]];
    dy[x]+=dy[F[x]];
    return F[x] = t;
}

int main()
{
    while (scanf("%d%d",&N,&M)==2)
    {
        memset(F,-1,sizeof(F));
        memset(dx,0,sizeof(dx));
        memset(dy,0,sizeof(dy));
        memset(ans,0,sizeof(ans));
        for (int i = 1; i <= M; ++i)
            scanf("%d%d%d%s",&F1[i],&F2[i],&L[i],D[i]);
        scanf("%d",&K);
        for (int i = 0; i < K; ++i)
        {
            scanf("%d%d%d",&node[i].u,&node[i].v,&node[i].i);
            node[i].inx=i;
        }
        sort(node, node+K, cmp);
        int t=1;
        for (int i = 0; i < K; ++i)
        {
            while (t<=M&&node[i].i>=t)
            {
                int t1=findd(F1[t]);
                int t2=findd(F2[t]);

                if (t1!=t2)
                {
                    F[t1]=t2;
                    if (D[t][0]=='N')
                    {
                        dy[t1]=dy[F2[t]]-dy[F1[t]]+L[t];
                        dx[t1]=dx[F2[t]]-dx[F1[t]];
                    } else if (D[t][0]=='S')
                    {
                        dy[t1]=dy[F2[t]]-dy[F1[t]]-L[t];
                        dx[t1]=dx[F2[t]]-dx[F1[t]];
                    } else if (D[t][0]=='E')
                    {
                        dx[t1]=dx[F2[t]]-dx[F1[t]]+L[t];
                        dy[t1]=dy[F2[t]]-dy[F1[t]];
                    } else if (D[t][0]=='W')
                    {
                        dx[t1]=dx[F2[t]]-dx[F1[t]]-L[t];
                        dy[t1]=dy[F2[t]]-dy[F1[t]];
                    }
                }
                t++;
            }
            if (findd(node[i].u)!=findd(node[i].v))
                ans[node[i].inx]=-1;
            else
                ans[node[i].inx]=abs(dx[node[i].u]-dx[node[i].v])+abs(dy[node[i].u]-dy[node[i].v]);
        }
        for (int i = 0; i < K; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}