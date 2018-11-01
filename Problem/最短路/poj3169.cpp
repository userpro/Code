// 差分约束
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
#define INF 1<<29
#define MAXN 1010
bool vis[MAXN];
int N, ML, MD;
int dis[MAXN], cnt[MAXN], edge[MAXN][MAXN];

void spfa(int start, int n)
{
    memset(cnt, 0, sizeof(cnt));
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
                    if (++cnt[i] > n)
                    {
                        printf("-1\n");
                        return;
                    }
                }
            }
        }
    }
    if (dis[N] == INF)
        printf("-2\n");
    else
        printf("%d\n", dis[N]);
}

int main()
{
    while (scanf("%d%d%d", &N, &ML, &MD) > 2 && N)
    {
        for (int i = 1; i <= N; ++i)
            for (int j = 0; j <= N; ++j)
                edge[i][j] = INF;
        int u, v, c;
        for (int i = 1; i <= ML; ++i)
        {
            scanf("%d%d%d", &u, &v, &c);
            edge[u][v] = c;
        }
        for (int i = 1; i <= MD; ++i)
        {
            scanf("%d%d%d", &u, &v, &c);
            edge[v][u] = -c;
        }
        spfa(1, N);
    }
    return 0;
}