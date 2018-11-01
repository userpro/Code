#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;
#define DIS(n1,n2) sqrt((n1.x-n2.x)*(n1.x-n2.x)+(n1.y-n2.y)*(n1.y-n2.y))
#define INF 1<<29
#define MAXN 210
typedef struct _pos
{
    double x, y;
}pos;
pos node[MAXN], sp[2];
bool vis[MAXN];
double cost[MAXN][MAXN], dis[MAXN];
int line[MAXN];

void spfa(int start, int n)
{
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= MAXN; ++i) dis[i] = INF;
    dis[start] = 0;
    vis[start] = 1;
    queue<int> que;
    que.push(start);
    while (!que.empty())
    {
        int t = que.front(); que.pop();
        vis[t] = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (dis[j] > dis[t] + cost[t][j])
            {
                dis[j] = dis[t] + cost[t][j];
                if (!vis[j])
                {
                    vis[j] = 1;
                    que.push(j);
                }
            }
        }
    }
}

int main()
{
    int ix, lix;
    double x, y, wk = 500/3.0, sby = 2000/3.0;
    memset(line, 0, sizeof(line));
    for (int i = 0; i <= MAXN; ++i)
    {
        for (int j = 0; j <= MAXN; ++j)
            cost[i][j] = INF;
        cost[i][i] = 0;
    }
    scanf("%lf%lf%lf%lf", &sp[0].x, &sp[0].y, &sp[1].x, &sp[1].y);

    ix = 0; lix = 0;
    while (scanf("%lf%lf", &x, &y) != EOF)
    {
        if (x == -1)
        {
            line[lix++] = ix;
            continue;
        }
        ++ix;
        node[ix].x = x;
        node[ix].y = y;
    }
    node[++ix] = sp[0]; node[++ix] = sp[1];

    for (int i = 1; i <= ix; ++i)
        for (int j = i+1; j <= ix; ++j)
            cost[i][j] = cost[j][i] = min(cost[j][i], DIS(node[i], node[j]) / wk);

    int a = 0, b = 0, c = 1;
    for (int i = 1; i <= ix - 2; ++i)
    {
        if (i == line[a])
        {
            c = b + 1;
            b = line[a++];
            for (int j = c; j < b; ++j)
                cost[j][j+1] = cost[j+1][j] = min(cost[j+1][j], DIS(node[j], node[j+1]) / sby);
        }
    }
    spfa(ix-1, ix);
    printf("%.0f\n", dis[ix]);
    return 0;
}