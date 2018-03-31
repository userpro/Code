#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
#define INF 1<<29
#define MAXN 110
bool vis[MAXN];
int N, A, B;
int dis[MAXN], edge[MAXN][MAXN];

void spfa(int start, int n)
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
            if (dis[i] > dis[t] + edge[t][i])
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
}

int main()
{
    while (scanf("%d%d%d", &N, &A, &B) > 2 && N)
    {
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                edge[i][j] = INF;
        int k1, k2;
        for (int i = 1; i <= N; ++i)
        {
            scanf("%d%d", &k1, &k2);
            edge[i][k2] = 0;
            for (int j = 2; j <= k1; ++j)
            {
                scanf("%d", &k2);
                edge[i][k2] = 1;
            }
        }
        spfa(A, N);
        if (dis[B] != INF)
            printf("%d\n", dis[B]);
        else
            printf("-1\n");
    }
    return 0;
}