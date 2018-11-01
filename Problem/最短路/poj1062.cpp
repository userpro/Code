#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>

using namespace std;
#define INF 1<<29
#define MAXN 110
bool vis[MAXN], legal[MAXN];
int M, N, P, L, X;
int price[MAXN], level[MAXN], dis[MAXN], edge[MAXN][MAXN];

void spfa(int start, int n)
{
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i)
        dis[i] = price[i];

    queue<int> que;
    for (int i = 1; i <= n; ++i)
    {
        if (legal[i])
        {
            vis[i] = 1;
            que.push(i);
        }
    }
    while (!que.empty())
    {
        int t = que.front(); que.pop();
        vis[t] = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (legal[i] && dis[i] > dis[t] + edge[t][i])
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
    while (scanf("%d%d", &M, &N) > 0 && M)
    {
        memset(price, 0, sizeof(price));
        memset(level, 0, sizeof(level));
        for (int i = 0; i <= N; ++i)
            for (int j = 0; j <= N; ++j)
                edge[i][j] = INF;

        int a, b;
        for (int i = 1; i <= N; ++i)
        {
            scanf("%d%d%d", &P, &L, &X);
            price[i] = P; level[i] = L;
            for (int j = 1; j <= X; ++j)
            {
                scanf("%d%d", &a, &b);
                edge[a][i] = b;
            }
        }

        int ans = INF;
        for (int i = 1; i <= N; ++i)
        {
            memset(legal, 0, sizeof(legal));
            int minlevel = level[i];
            for (int j = 1; j <= N; ++j)
                if (minlevel - level[j] <= M && minlevel >= level[j])
                    legal[j] = 1;
            spfa(i, N);
            if (ans > dis[1])
                ans = dis[1];
        }
        printf("%d\n", ans);
    }
    return 0;
}