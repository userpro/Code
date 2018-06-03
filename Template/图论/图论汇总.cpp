#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN = 1000;
const int INF = 0x3f3f3f3f;

//染色
//判断结点u所在的连通分量是否为二分图
//未染色结点值为0， 已染色结点值为1/2.
int color[MAXN];
bool bipartite(int u) {
    for(int i = 0; i < G[u].size(); i++){
        int v = G[u][i];                      //枚举每条边(u, v)
        if(color[v] == color[u]) return false;//结点v已着色，且和结点u的颜色冲突
        if(!color[v]) {
            color[v] = 3 - color[u];          //给结点v着与结点u相反的颜色
            if(!bipartite(v)) return false;
        }
    }
    return true;
}

//无向图求桥求割
struct Edge{
    int v, w;
    bool cut;
    Edge(int v, int w, int cnt = false) : v(v), w(w), cut(cut) {}
};
bool iscut[MAXN];
vector<Edge> G[MAXN];
int dfs_clock, low[MAXN], pre[MAXN];

int dfs(int u, int fa) {    //u在DFS树中的父节点是fa
    int lowu = pre[u] = ++dfs_clock;
    bool flag = false;
    int child = 0;          //子节点数目
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].v;
        if(!pre[v]) {
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);         //用后代的low函数更新u的low函数
            if(lowv >= pre[u]) {
                if(lowv > pre[u]) G[u][i].cut = true;
                iscut[u] = true;
            }
        } else if(v == fa) {
            if(flag) lowu = min(lowu, pre[v]);
            flag = true;
        } else lowu = min(lowu, pre[v]);       //用反向边更新u的low函数
    }
    if(fa < 0 && child == 1) iscut[u] = 0;
    low[u] = lowu;
    return lowu;
}

//有向图的强连通分量
vector<int> G[MAXN];
int pre[MAXN], low[MAXN], sccno[MAXN], dfs_clock, scc_cnt;
stack<int> S;

void Tarjan(int u) {
    pre[u] = low[u] = ++dfs_clock;
    S.push(u);
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!pre[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(!sccno[v]) low[u] = min(low[u], pre[v]);
    }
    if(low[u] == pre[u]) {
        scc_cnt++;
        while(true) {
            int x = S.top();
            S.pop();
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
}

void find_scc(int n) {
    dfs_clock = scc_cnt = 0;
    memset(sccno, 0 , sizeof(sccno));
    memset(pre, 0, sizeof(pre));
    for(int i = 0; i < n; i++)
        if(!pre[i]) Tarjan(i);
}

//2-SAT
struct TwoSAT {
    stack<int> S;
    vector<int> G[MAXN*2];
    int n, dfs_clock, scc_cnt;
    int pre[MAXN*2], low[MAXN*2], sccno[MAXN*2];

    void init(int n) {
        this->n = n;
        for(int i = 0; i < MAXN*2; i++) g[i].clear();
    }

    void addEdge(int x, int xv, int y, int yv) {
        x = x*2 + xv;
        y = y*2 + yv;
        g[x].push_back(y);
    }

    void dfs(int u) {
        pre[u] = low[u] = ++dfs_clock;
        S.push(u);
        for(int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if(!pre[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if(!sccno[v]) low[u] = min(low[u], pre[v]);
        }
        if(low[u] == pre[u]) {
            scc_cnt++;
            while(true) {
                int x = S.top();
                S.pop();
                sccno[x] = scc_cnt;
                if(x == u) break;
            }
        }
    }

    void find_scc() {
        dfs_clock = scc_cnt = 0;
        memset(pre, 0, sizeof pre);
        memset(sccno, 0, sizeof sccno);
        for(int i = 0; i < n*2; i++) if(!pre[i]) dfs(i);
    }

    bool solve() {
        find_scc();
        for(int i = 0; i < n; i++)
            if(sccno[i*2] == sccno[i*2+1]) return false;
        return true;
    }
};


//Dijkstra(O(n2))
bool vis[MAXN];
int n, d[MAXN];
int w[MAXN][MAXN];
int fa[MAXN];
void Dijkstra(int s) {
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < n; i++) d[i] == (i == s ? 0 : INF);
    for(int i = 0; i < n; i++) {
        int x, m = INF;
        for(int y = 0; y < n; y++) if(!vis[y] && d[y] <= m) m = d[x=y];
        vis[x] = true;
        for(int y = 0; y < n; y++)
        if(d[y] > d[x] + w[x][y]) {
            d[y] = d[x] + w[x][y];
            fa[y] = x;
        }
    }
}

//Dijkstra+HeapNode(O(m*lgn))
struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};
struct HeapNode {
    int d, u;
    HeapNode() {}
    HeapNode(int d, int u) : d(d), u(u) {}

    bool operator < (const HeapNode& rhs) const {
        return d > rhs.d;
    }
};
struct Dijkstra {
    int n, m;
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool done[MAXN];
    int d[MAXN];
    int p[MAXN];

    void init(int n) {
        this -> n = n;
        for(int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }

    void addEdge(int u, int v, int w) {
        edges.push_back(Edge(u, v, w));
        G[u].push_back(edges.size()-1);
    }

    void dijkstra(int s) {
        priority_queue<HeapNode> Q;
        for(int i = 0; i <= n; i++) d[i] = INF;
        d[s] = 0;
        memset(done, 0, sizeof(done));
        Q.push(HeapNode(0,s));
        while(!Q.empty()) {
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if(done[u]) continue;
            done[u] = true;
            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(d[e.v] > d[u] + e.w) {
                    d[e.v] = d[u] + e.w;
                    p[e.v] = G[u][i];
                    Q.push(HeapNode(d[e.v], e.v));
                }
            }
        }
    }
};

//Floyed算法
void Floyed() {
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
}

//SPFA(BFS)
void SPFA(int s) {
    queue<int> Q;
    d[s] = 0;
    Q.push(s);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to, w = edge[i].w;
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w;
                Q.push(v);
            }
        }
    }
}

//SPFA(DFS)
bool spfa(int u) {
    vis[u] = 1;
    for(int v = 1; v <= n; v++) {
        if(mp[u][v] && d[u] + e[v] > d[v] && d[u] + e[v] > 0) {
            d[v] = d[u] + e[v];
            if(!vis[v]) {
                if(spfa(v)) return true;
            } else return reach[v][n];
        }
    }
    vis[u] = 0;
    return d[n] > 0;
}

//两个条件下的最短路 HDU1245
void SPFA() {
    for(int i = 0; i < MAXN; i++) dis[i] = step[i] = INF, vis[i] = 0;
    queue<int> Q;
    dis[0] = step[0] = 0, vis[0] = 1;
    Q.push(0);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        vis[u] = 0;
        for(int j = 0; j < G[u].size(); j++) {
            int v = G[u][j].v;
            double len = G[u][j].dist;
            if(abs(dis[v]-dis[u]-len) <= EPS) {
                if(step[v] > step[u]+1)
                    step[v] = step[u]+1;
            } else if(dis[v] >= dis[u]+len) {
                dis[v] = dis[u]+len;
                step[v] = step[u]+1;
                if(!vis[v]) {
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

//Prim
int Prim() {
    int s = 0, cnt = 1, ans = 0, pos, low[MAXN];
    bool vis[MAXN];
    for(int i = 0; i <= n; i++) low[i] = INF, vis[i] = false;
    vis[s] = true;
    while(true) {
        if(cnt == n) break;
        int mn = INF;
        for(int j = 1; j < n; j++) {
            if(!vis[j] && low[j] > dist[s][j]) low[j] = dist[s][j];
            if(!vis[j] && mn > low[j]) mn = low[pos=j];
        }
        vis[s=pos] = true;
        ans += mn;
        cnt++;
    }
    return ans;
}

//Kruskal
void Kruskal() {
    ans = 0;
    for(int i = 0; i <= n; i++) fa[i] = i;
    for(unsigned i = 0; i < G.size(); i++) {
        int u = G[i].u, v = G[i].v, w = G[i].w;
        int x = Find(u), y = Find(v);
        if(x != y) {
            ans += w;
            fa[y] = x;
        }
    }
    printf("%d\n", ans);
}

//匈牙利算法（二分图最大匹配）O(|E|*sqrt(|V|))
bool vis[MAXN];
vector<int> G[MAXN];
int n, m, k, head[MAXN];

bool match(int x) {
    for(unsigned i = 0; i < G[x].size(); i++) {
        if(!vis[G[x][i]]) {
            vis[G[x][i]] = true;
            if(head[G[x][i]] == -1 || match(head[G[x][i]])) {
                head[G[x][i]] = x;
                return true;
            }
        }
    }
    return false;
}

int hungary() {
    int res = 0;
    memset(head, -1, sizeof(head));
    for(int i = 0; i < n; i++) {
        memset(vis, 0, sizeof(vis));
        if(match(i)) res++;
    }
    return res;
}


//最小树形图
/********************************************************************
* 给定一个有向图， 求以某个给定顶点为根的有向生成树(也就是说沿着
  这N-1条边可以从根走到任意点)，使权和最小。
* 判断是否存在最小树形图，以根为起点DFS一遍即可。
*********************************************************************/
double G[MAXN][MAXN];
int used[MAXN], pass[MAXN], eg[MAXN], more, Queue[MAXN], n, m;

inline void combine(int id, double& sum) {
    int tot = 0, from;
    for(; id != 0 && !pass[id]; id = eg[id]) {
        Queue[tot++] = id;
        pass[id] = 1;
    }
    for(from = 0; from < tot && Queue[from] != id; ++from);
    if(from == tot) return;
    more = 1;
    for(int i = from; i < tot; i++) {
        sum += G[eg[Queue[i]]][Queue[i]];
        if(i != from) {
            used[Queue[i]] = 1;
            for(int j = 1; j <= n; j++) if(!used[j]) {
                    if(G[Queue[i]][j] < G[id][j])
                        G[id][j] = G[Queue[i]][j];
                }
        }
    }
    for(int i = 1; i <= n; ++i) if(!used[i] && i != id) {
            for(int j = from; j < tot; ++j) {
                int k = Queue[j];
                if(G[i][id] > G[i][k] - G[eg[k]][k])
                    G[i][id] = G[i][k] - G[eg[k]][k];
            }
        }
}

inline double mdst(int root) {
    double sum = 0;
    memset(used, 0, sizeof(used));
    for(more = 1; more; ) {
        more = 0;
        memset(eg, 0, sizeof(eg));
        for(int i = 1; i <= n; ++i)
    }
}

//最大流Dinic算法(O(N^2*M))
struct Edge{
    int from, to, cap, flow;
    Edge() {}
    Edge(int from, int to, int cap, int flow) : from(from), to(to), cap(cap), flow(flow) {}
};

struct Dinic {
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];


    void AddEdge(int from, int to, int cap) {
//        cout << from << "<=====> " << to <<  "   "<< cap << endl;
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS() {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while(!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for(int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if(!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a) {
        if(x == t || a == 0) return a;
        int flow = 0, f;
        for(int& i = cur[x]; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0 ) {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    int MaxFlow(int s, int t) {
        this-> s = s;
        this-> t = t;
        int flow = 0;
        while(BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
//        cout << flow << endl;
        return flow;
    }
};

//最小费用最大流
//是否在队列中
bool vis[MAXN];
//a可改尽量 p上一条弧 d费用
int a[MAXN], p[MAXN], d[MAXN];
//最大流, 最小费用
int flow, cost, n, m;

struct Edge {
    int from, to, cap, flow, cost;
    Edge() {}
    Edge(int from, int to, int cap, int flow, int cost) : from(from), to(to), cap(cap), flow(flow), cost(cost) {}
};

vector<Edge> edges;
vector<int> G[MAXN];

inline void init() {
    flow = cost = 0;
    for(int i = 0; i <= n; i++) G[i].clear();
    edges.clear();
}

void addEdge(int from, int to, int cap, int cost) {
    edges.push_back(Edge(from, to, cap, 0, cost));
    edges.push_back(Edge(to, from, 0, 0, -cost));
    int m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
}

bool spfa(int s, int t, int& flow, int& cost) {
    for(int i = 0; i <= n; i++) d[i] = INF;
    memset(vis, false, sizeof(vis));
    d[s] = 0, vis[s] = true, p[s] = 0, a[s] = INF;
    queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        for(int i = 0; i < G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                d[e.to] = d[u] + e.cost;
                p[e.to] = G[u][i];
                a[e.to] = min(a[u], e.cap - e.flow);
                if(!vis[e.to]) Q.push(e.to), vis[e.to] = 1;
            }
        }
    }
    if(d[t] == INF) return false;
    flow += a[t], cost += d[t] * a[t];
    int u = t;
    while(u != s) {
        edges[p[u]].flow += a[t];
        edges[p[u]^1].flow -= a[t];
        u = edges[p[u]].from;
    }
    return true;
}

int main() {
    return 0;
}
