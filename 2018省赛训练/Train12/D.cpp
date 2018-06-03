#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAX 410
bool G1[MAX][MAX],G2[MAX][MAX],inq[MAX];

bool vis[MAX];
int dis[MAX], edge[MAX][MAX];

int spfa(int start, int n, bool edge[MAX][MAX])
{
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i) dis[i] = INF;
    dis[start] = 0;
    vis[start] = 1;
    queue<int> que;
    que.push(start);
    while (!que.empty())
    {
        int t = que.front(); que.pop();
        vis[t] = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (edge[t][i] && dis[i] > dis[t] + edge[t][i])
            {
                dis[i] = dis[t] + edge[t][i];
                if (!vis[i])
                {
                    vis[i] = 1;
                    que.push(i);
                }
            }
        }
    }
    return dis[n];
}

int N,M;
int u,v;
int main()
{
    while (scanf("%d%d",&N,&M)!=EOF)
    {
        CLR(G1,1);
        CLR(G2,0);
        for (int i=0;i<M;i++)
        {
            scanf("%d%d",&u,&v);
            G2[u][v]=G2[v][u]=1;
            G1[u][v]=G1[v][u]=0;
        }
        for (int i=0;i<MAX;i++)
            G1[i][i]=0, G2[i][i]=0;

        int d1=spfa(1,N,G1), d2=spfa(1,N,G2);
        // printf("%d %d\n", d1,d2);
        if (d1 == INF || d2 == INF)
            printf("-1\n");
        else
            printf("%d\n", max(d1,d2));
    }
    return 0;
}