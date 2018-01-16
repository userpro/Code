#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 110
#define INF 1<<29
int N;
int D[MAXN][MAXN], dis[MAXN];
bool vis[MAXN];

void prim(int n)
{
    memset(vis,0,sizeof(vis));
    for (int i = 0; i < n; ++i)
        dis[i]=INF;

    int ans=0;
    dis[0]=0;
    for (int i = 0; i < n; ++i)
    {
        int minn=INF,k;
        for (int j = 0; j < n; ++j)
        {
            if (!vis[j]&&minn>dis[j])
            {
                minn=dis[j];
                k=j;
            }
        }
        vis[k]=1;
        ans+=dis[k];
        for (int j = 0; j < n; ++j)
        {
            if (!vis[j])
                dis[j]=min(D[k][j], dis[j]);
        }
    }
    printf("%d\n", ans);
}

int main()
{
    while (scanf("%d",&N)==1 && N)
    {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                D[i][j]=INF;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                scanf("%d",&D[i][j]);
        prim(N);
    }
    return 0;
}