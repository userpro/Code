#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
#define INF 1<<29
#define MAXM 200010
#define MAXN 200010
struct Edge
{
    int from, to, cap, flow;
    Edge(int f, int t, int c, int fw):from(f),to(t),cap(c),flow(fw) {}
};

struct Dinic
{
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];

    void init(int n)
    {
        for (int i = 0; i < n; ++i) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap)
    {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS()
    {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!Q.empty())
        {
            int x = Q.front(); Q.pop();
            for (int i = 0; i < G[x].size(); ++i)
            {
                Edge &e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow)
                {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a)
    {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int &i = cur[x]; i < G[x].size(); ++i)
        {
            Edge &e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0)
            {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int Maxflow(int s, int t)
    {
        this->s = s; this->t = t;
        int flow = 0;
        while (BFS())
        {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
};

struct qnode
{
    int v, c;
    qnode(int _v=0, int _c=0):v(_v), c(_c) {}
};
struct MEdge
{
    int v, cost;
    MEdge(int _v=0, int _cost=0):v(_v), cost(_cost) {}
};

bool vis[MAXM];
int dis1[MAXM], dis2[MAXM];
vector<MEdge> E[MAXM];
int T, N, M, A, B;
int a[MAXM], b[MAXM], c[MAXM];

void spfa(int n, int start, int dis[MAXM])
{
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i <= N; ++i) dis[i] = INF;
    dis[start] = 0;
    vis[start] = 1;
    queue<qnode> que;
    que.push(qnode(start, 0));
    qnode tmp;
    while (!que.empty())
    {
        tmp = que.front(); que.pop();
        int v = tmp.v;
        if (!vis[v]) continue;
        vis[v] = 0;
        for (int i = 0; i < E[v].size(); ++i)
        {
            MEdge e = E[v][i];
            if (dis[e.v] > dis[v] + e.cost)
            {
                dis[e.v] = dis[v] + e.cost;
                if (!vis[e.v])
                {
                    vis[e.v] = 1;
                    que.push(qnode(e.v, dis[e.v]));
                }
            }
        }
    }
}

void add_edge(int u, int v, int w)
{
    E[u].push_back(MEdge(v, w));
}

int main()
{
    while (scanf("%d", &T) > 0 && T)
    {
        for (int i = 1; i <= T; ++i)
        {
            scanf("%d%d", &N, &M);
            for (int j = 1; j <= M; ++j) E[j].clear();
            for (int j = 1; j <= M; ++j)
            {
                scanf("%d%d%d", &a[j], &b[j], &c[j]);
                if (a[j] != b[j]) add_edge(a[j], b[j], c[j]);
            }
            scanf("%d%d", &A, &B);
            spfa(N, A, dis1);
            for (int j = 1; j <= M; ++j) E[j].clear();
            for (int j = 1; j <= M; ++j)
                add_edge(b[j], a[j], c[j]);
            spfa(N, B, dis2);
            Dinic ek;
            ek.init(N);
            for (int j = 1; j <= M; ++j)
            {
                if (a[j] != b[j] && dis1[a[j]] + dis2[b[j]] + c[j] == dis1[B])
                    ek.AddEdge(a[j], b[j], 1);
            }
            printf("%d\n", ek.Maxflow(A, B));
        }
    }
    return 0;
}