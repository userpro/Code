#include <cstdio>
#include <cstring>

#define INF 1<<20
#define MAX 1010
bool vis[MAX];
int mp[MAX][MAX], dis1[MAX], dis2[MAX];
int N, M, X, i, j, k, l;

void dijk(int dis[MAX])
{
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= N; ++i)
        dis[i] = mp[1][i];

    vis[1] = 1;
    dis[1] = 0;
    for (i = 1; i <= N; ++i)
    {
        k = INF;
        for (j = 1; j <= N; ++j)
        {
            if (!vis[j] && k > dis[j])
            {
                k = dis[j];
                l = j;
            }
        }
        vis[l] = 1;
        for (j = 1; j <= N; ++j)
        {
            if (!vis[j] && dis[j] > dis[l] + mp[l][j])
                dis[j] = dis[l] + mp[l][j];
        }
    }
}

int main()
{
    while (scanf("%d%d%d", &N, &M, &X) != EOF && N)
    {
        for (i = 0; i < MAX; ++i)
            for (j = 0; j < MAX; ++j)
                if (i != j) mp[i][j] = INF;
                else mp[i][j] = 0;

        for (i = 0; i < M; ++i)
        {
            scanf("%d%d%d", &j, &k, &l);
            if (j == 1) j = X;
            else if (j == X) j = 1;
            if (k == 1) k = X;
            else if (k == X) k = 1;
            mp[j][k] = l;
        }

        dijk(dis1);

        for (i = 1; i <= N; ++i)
            for (j = i; j <= N; ++j)
                {
                    k = mp[i][j];
                    mp[i][j] = mp[j][i];
                    mp[j][i] = k;
                }

        dijk(dis2);

        l = 0;
        for (i = 1; i <= N; ++i)
            if (l < dis1[i]+dis2[i])
                l = dis1[i]+dis2[i];

        printf("%d\n", l);
    }
    return 0;
}