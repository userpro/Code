#define MAX 310

bool vis[MAX];
int dis[MAXN], edge[MAXN][MAXN];

// n个顶点 1~n
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