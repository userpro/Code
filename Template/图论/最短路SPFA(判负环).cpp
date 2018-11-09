#include <vector>
#include <cstring>
const int inf=1<<29;
const int maxn=110;

struct Edge
{
    int v,w,nx;
}edge[maxn<<1];
int cnt;
int head[maxn]
bool vis[maxn];
int dis[maxn],num[maxn];

void _init() {
    cnt=0;
    memset(head,-1,sizeof(head));
}

void add(int u,int v,int w) {
    edge[cnt].v = v; edge[cnt].w = w;
    edge[cnt++].nx = head[u];
    edge[cnt].v = u; edge[cnt].w = w;
    edge[cnt++].nx = head[v];
}

// n个顶点 1~n
// 返回bool 是否存在负环
bool spfa(int start, int n) {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i) dis[i] = inf;
    dis[start] = 0;
    vis[start] = 1;
    queue<int> que;
    que.push(start);
    while (!que.empty()) {
        int u = que.front(); que.pop();
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = edge[i].nx) {
            int v = edge[i].v;
            cnt[v] = cnt[u] + 1;
            if (cnt[v] > n) return false; // 存在负环
            if (dis[v] > dis[u] + edge[i].w) {
                dis[v] = dis[u] + edge[i].w;
                if (!vis[v]) {
                    vis[v] = 1;
                    que.push(v);
                }
            }
        }
    }
    return true;
}