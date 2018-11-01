#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 110
bool vis[MAXN];
int G[MAXN][MAXN],G1[MAXN][MAXN];
int T,N,M;
int ans;

int a,b,c;
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        for (int jj=1;jj<=T;jj++)
        {
            ans=0;
            for (int i=0;i<MAXN;i++)
                for (int j=0;j<MAXN;j++)
                    G[i][j]=i==j?0:INF;

            scanf("%d%d",&N,&M);
            for (int i=0;i<M;i++)
            {
                scanf("%d%d%d",&a,&b,&c);
                if (G[a][b]==INF)
                {
                    G[a][b]=c;
                    G[b][a]=c;
                }
                else
                {
                    G[b][a]=G[a][b]=min(G[a][b],c);
                    ans++;
                }
            }

            memcpy(G1,G,sizeof(G));
            for (int k=1;k<=N;k++)
                for (int i=1;i<=N;i++)
                    for (int j=1;j<=N;j++)
                        if (G[i][k]+G[k][j]<G[i][j])
                            G[i][j]=G[i][k]+G[k][j];

            for (int i=1;i<=N;i++)
                for (int j=i+1;j<=N;j++)
                    for (int k=1;k<=N;k++)
                    {
                        if (G[i][j]<G1[i][j]&&G1[i][j]!=INF)
                        {
                            ans++;
                            break;
                        }
                        if (G[i][j]==G[i][k]+G[k][j]&&G1[i][j]!=INF&&i!=k&&j!=k)
                        {
                            ans++;
                            break;
                        }
                    }

            printf("Case %d: %d\n", jj,ans);
        }
    }
    return 0;
}