#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define mem(a,b) (memset(a,b,sizeof(a)))
#define MAXN 510
int N,M;
bool E[MAXN][MAXN];
int ind[MAXN];
bool vis[MAXN];

int main()
{
    while (scanf("%d%d",&N,&M)==2)
    {
        mem(ind,0); mem(E,0); mem(vis,0);
        int u,v;
        for (int i = 1; i <= M; ++i)
        {
            scanf("%d%d",&u,&v);
            if (!E[u][v])
            {
                E[u][v]=1;
                ind[v]++;
            }
        }
        int cnt=0;
        while (cnt<N)
        {
            for (int i = 1; i <= N; ++i)
            {
                if (!vis[i]&&ind[i]==0)
                {
                    cnt++;
                    if (cnt==N)
                        printf("%d\n", i);
                    else
                        printf("%d ", i);
                    for (int j = 1; j <= N; ++j)
                    {
                        if (E[i][j])
                            ind[j]--;
                    }
                    vis[i]=1;
                    break;
                }
            }
        }
    }
    return 0;
}