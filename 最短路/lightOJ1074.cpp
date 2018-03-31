#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
#define MAX 210
#define POW3(n1,n2) ((n1-n2)*(n1-n2)*(n1-n2))
#define INF 1<<29
typedef struct _pos
{
    int from, to, cost;
}pos;
pos edge[MAX*MAX];
bool inq[MAX*MAX];
int T, n, m, q, i, j, k, l, x;
int busyness[MAX], dis[MAX], R[MAX], First[MAX], Next[MAX*MAX], cnt[MAX];

void dfs(int y)
{
    R[y] = 1;
    for (int z = First[y]; z != -1; z = Next[z])
        if (!R[edge[z].to])
            dfs(edge[z].to);
}

void bellman_ford()
{
    memset(inq, 0, sizeof(inq));
    memset(R, 0, sizeof(R));
    for (i = 1; i <= n; ++i) 
    {
        First[i] = -1;
        cnt[i] = 0;
        dis[i] = INF;
    }
    for (i = 1; i <= m; ++i)
    {
        Next[i] = First[edge[i].from];
        First[edge[i].from] = i;
    }
    queue<int> q;
    q.push(1);
    dis[1] = 0;
    inq[1] = true;
    while (!q.empty())
    {
        int y = q.front(); q.pop();
        inq[y] = false;
        for (int z = First[y]; z != -1; z = Next[z])
        {
            if (R[edge[z].to]) 
                continue;
            if (dis[y] < INF && dis[edge[z].to] > dis[y] + edge[z].cost)
            {
                dis[edge[z].to] = dis[y] + edge[z].cost;
                if (!inq[edge[z].to])
                {
                    inq[edge[z].to] = true;
                    q.push(edge[z].to);
                    if (++cnt[edge[z].to] > n)
                        dfs(edge[z].to);
                }
            }
        }
    }
}

int main()
{
    while (scanf("%d", &T) > 0 && T)
    {
        for (l = 1; l <= T; ++l)
        {
            printf("Case %d:\n", l);
            memset(busyness, 0, sizeof(busyness));
            scanf("%d", &n);
            for (i = 1; i <= n; ++i)
                scanf("%d", &busyness[i]);
            scanf("%d", &m);
            for (i = 1; i <= m; ++i)
            {
                scanf("%d%d", &edge[i].from, &edge[i].to);
                edge[i].cost = POW3(busyness[edge[i].to], busyness[edge[i].from]);
            }
            bellman_ford();
            scanf("%d", &q);
            for (i = 1; i <= q; ++i)
            {
                scanf("%d", &x);
                if (dis[x] >= 3 && !R[x] && dis[x] != INF)
                    printf("%d\n", dis[x]);
                else
                    printf("?\n");
            }
        }
    }
    return 0;
}