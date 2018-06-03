#include <queue>
#define INF (1<<29)
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
vector<Edge> E[MAX]; // 记得初始化
bool vis[MAX],dis[MAX];

// n个顶点 1~n
void dijk(int start, int n)
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