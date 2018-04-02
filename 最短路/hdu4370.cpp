// spfa
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
#define INF 1<<29
#define MAX 310

bool vis[MAX];
int dis[MAX], cost[MAX][MAX];
int N;

void spfa(int s, int n)
{
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= N; ++i) dis[i] = INF;
    queue<int> que;
    for (int i = 2; i <= N; ++i)
        if (i != s)
        {
            dis[i] = cost[s][i];
            vis[i] = 1;
            que.push(i);
        }

    while (!que.empty())
    {
        int t = que.front(); que.pop();
        vis[t] = 0;
        for (int i = 1; i <= N; ++i)
        {
            if (dis[i] > dis[t] + cost[t][i])
            {
                dis[i] = dis[t] + cost[t][i];
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
    while (scanf("%d", &N) > 0 && N)
    {
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                scanf("%d", &cost[i][j]);
        spfa(1, N);
        int path = dis[N];
        int loop1 = dis[1];
        spfa(N, N);
        int loopn = dis[N];
        int ans = min(path, loopn+loop1);
        printf("%d\n", ans);
    }
    return 0;
}