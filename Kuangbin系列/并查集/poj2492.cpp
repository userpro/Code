#include <cstdio>
#include <cstring>

#define MAXN 2010
int F[MAXN], val[MAXN];
int T,N,M;

int findd(int x)
{
    if (-1==F[x]) return x;
    int t=findd(F[x]);
    val[x]^=val[F[x]];
    return F[x]=t;
}

int main()
{
    int u,v,flag;
    scanf("%d",&T);
    for (int i = 1; i <= T; ++i)
    {
        flag=1;
        memset(F,-1,sizeof(F));
        memset(val,0,sizeof(val));
        scanf("%d%d",&N,&M);
        for (int j=0; j<M; ++j)
        {
            scanf("%d%d",&u,&v);
            if (!flag) continue;

            int a=findd(u);
            int b=findd(v);
            if (a!=b)
            {
                F[a]=b;
                val[a]=val[v]^val[u]^1;
            } else if (val[u]==val[v])
            {
                flag=0;
            }
        }
        printf("Scenario #%d:\n", i);
        if (flag)
            printf("No suspicious bugs found!\n\n");
        else
            printf("Suspicious bugs found!\n\n");
    }
    return 0;
}