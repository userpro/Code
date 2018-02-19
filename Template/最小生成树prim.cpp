#include <cstdio>
#include <cstring>

#define MAXN 1000
#define INF 1<<29
bool vis[MAXN];
int lowc[MAXN],d[MAXN][MAXN];

void prim(int n)
{
    memset(vis,0,sizeof(vis));
    for (int i = 0; i < MAXN; ++i)
        lowc[i]=INF;

    for (int i = 0; i < n; ++i)
    {
        int minn=INF,k;
        for (int j = 0; j < n; ++j)
        {
            if (!vis[j]&&minn>lowc[j])
            {
                minn=lowc[j];
                k=j;
            }
        }
        vis[k]=1;
        for (int j = 0; j < n; ++j)
        {
            if (!vis[j]&&lowc[j]>d[k][j])
                lowc[j]=d[k][j];
        }
    }
}

int main()
{
    /* code */
    return 0;
}