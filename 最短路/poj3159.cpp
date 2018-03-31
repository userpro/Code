#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
#define INF (-1^(1<<31))
#define MAX_N 30010
#define MAX_M 150010
typedef struct _pos
{
    int from, to, cost;
}pos;
pos edge[MAX_M];
bool vis[MAX_N];
int FIRST[MAX_M], NEXT[MAX_M], dis[MAX_N], S[MAX_N];
int N, M, i, j, k, l, m, frontq, tailq;

void spfa()
{
    memset(vis, 0, sizeof(vis));
    memset(FIRST, -1, sizeof(FIRST));
    memset(NEXT, -1, sizeof(NEXT));
    for (i = 1; i <= N; ++i) 
        dis[i] = INF;
    for (i = 1; i <= M; ++i)
    {
        NEXT[i] = FIRST[edge[i].from];
        FIRST[edge[i].from] = i;
    }

    int top = 0;
    S[top++] = 1;
    vis[1] = 1;
    dis[1] = 0;
    while (top != 0)
    {
        l = S[--top];
        vis[l] = 0;
        for (j = FIRST[l]; j != -1; j = NEXT[j])
        {
            if (dis[edge[j].to] > dis[edge[j].from] + edge[j].cost)
            {
                dis[edge[j].to] = dis[edge[j].from] + edge[j].cost;
                if (!vis[edge[j].to])
                {
                    vis[edge[j].to] = 1;
                    S[top++] = edge[j].to;
                }
            }
        }
    }
}

int main()
{
    while (scanf("%d%d", &N, &M) > 1 && N)
    {
        pos tmp;
        for (i = 1; i <= M; ++i)
        {
            scanf("%d%d%d", &tmp.from, &tmp.to, &tmp.cost);
            edge[i] = tmp;
        }
        spfa();
        printf("%d\n", dis[N]);
    }
    return 0;
}