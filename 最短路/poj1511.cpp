#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>

using namespace std;
#define INF 1<<30
#define MAX 1000100
#define uint unsigned long long
typedef struct _pos
{
    int from, to, cost;
}pos;
pos E[MAX];
bool vis[MAX];
int FIRST[MAX], NEXT[MAX];
int dis[MAX];
int N, P, Q, i, j, k, m;
uint ans;

uint spfa(int start)
{
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= P; ++i) 
    {
        FIRST[i] = -1;
        dis[i] = INF;
    }

    for (i = 1; i <= Q; ++i)
    {
        NEXT[i] = FIRST[E[i].from];
        FIRST[E[i].from] = i;
    }

    uint ret;
    queue<int> q;
    vis[start] = 1;
    dis[start] = 0;
    q.push(start);
    while (!q.empty())
    {
        j = FIRST[q.front()]; q.pop();
        vis[j] = 0;
        while (j != -1)
        {
            if (dis[E[j].to] > dis[E[j].from] + E[j].cost)
            {
                dis[E[j].to] = dis[E[j].from] + E[j].cost;
                if (!vis[E[j].to])
                {
                    vis[E[j].to] = 1;
                    q.push(E[j].to);
                }
            }
            j = NEXT[j];
        }
    }

    for (ret = 0, i = 1; i <= P; ++i) ret += dis[i];
    return ret;
}

int main()
{
    while (scanf("%d", &N) > 0 && N)
    {
        pos tmp;
        for (m = 0; m < N; ++m)
        {
            scanf("%d%d", &P, &Q);
            for (i = 1; i <= Q; ++i)
            {
                scanf("%d%d%d", &tmp.from, &tmp.to, &tmp.cost);
                E[i] = tmp;
            }

            ans = 0;
            ans += spfa(1);

            for (i = 1; i <= Q; ++i)
                swap(E[i].from, E[i].to);

            ans += spfa(1);
            printf("%llu\n", ans);
        }
    }
    return 0;
}