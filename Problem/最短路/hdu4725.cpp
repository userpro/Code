#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;
#define INF 1<<29
#define MAX 500010
struct qnode
{
    int v, c;
    qnode(int _v=0, int _c=0):v(_v), c(_c) {}
    bool operator <(const qnode &r) const
    {
        return c > r.c;
    }
};
struct Edge
{
    int v, cost;
    Edge(int _v=0, int _cost=0):v(_v), cost(_cost) {}
};
vector<Edge> E[MAX];
bool vis[MAX];
int dis[MAX];
int T, N, M, C, i, j, k, x, y, z;

void dijk(int n, int start)
{
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= n; ++i) dis[i] = INF;
    priority_queue<qnode> que;
    while (!que.empty()) que.pop();
    dis[start] = 0;
    que.push(qnode(start, 0));
    qnode tmp;
    while (!que.empty())
    {
        tmp = que.top();
        que.pop();
        int u = tmp.v;
        if (vis[u]) continue;
        vis[u] = 1;
        for (i = 0; i < E[u].size(); ++i)
        {
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if (!vis[v] && dis[v] > dis[u] + cost)
            {
                dis[v] = dis[u] + cost;
                que.push(qnode(v, dis[v]));
            }
        }
    }
}

void add_edge(int u, int v, int w)
{
    E[u].push_back(Edge(v, w));
}

int main()
{
    while (scanf("%d", &T) > 0 && T)
    {
        for (int l = 1; l <= T; ++l)
        {
            printf("Case #%d: ", l);
            scanf("%d%d%d", &N, &M, &C);
            for (i = 1; i <= N*3; ++i) 
                E[i].clear();

            for (i = 1; i <= N; ++i)
            {
                scanf("%d", &j);
                add_edge(i, N + 2*j - 1, 0);
                add_edge(N + 2*j, i, 0);
            }

            for (i = 1; i < N; ++i)
            {
                add_edge(N + 2*i - 1, N + 2*(i+1), C);
                add_edge(N + 2*(i+1) - 1, N + 2*i, C);
            }
            
            int u, v, w;
            for (i = 1; i <= M; ++i)
            {
                scanf("%d%d%d", &u, &v, &w);
                add_edge(u, v, w);
                add_edge(v, u, w);
            }
            dijk(N*3, 1);
            if (dis[N] != INF)
                printf("%d\n", dis[N]);
            else
                printf("-1\n");
        }
    }
    return 0;
}