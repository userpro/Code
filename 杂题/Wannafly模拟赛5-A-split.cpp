#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
#define ll unsigned long long int
#define MAXS 1010
#define INF 1<<29
int S, dis[MAXS];
ll M, val[MAXS];
bool vis[MAXS];

void solve(int n, ll m)
{
    memset(vis, 0, sizeof(vis));
    memset(val, 0, sizeof(val));
    for (int i = 0; i <= n; ++i)
        dis[i]=INF;
    queue<int> q, q1;
    dis[n] = 0;
    vis[n] = 1;
    q.push(n);
    while (!q.empty())
    {
        int t = q.front(); q.pop();
        vis[t] = 0;
        for (int i = 1; i < t; ++i)
        {
            ll v = val[t] + i*(t-i);
            if (v > val[i])
            {
                dis[i]=dis[t]+1;
                val[i] = v;
                if (v >= m)
                    q1.push(dis[i]);
                else if (!vis[i])
                {
                    vis[i] = 1;
                    q.push(i);
                }
            }
        }
    }
    int ans = INF;
    while (!q1.empty())
    {
        int t = q1.front(); q1.pop();
        ans = min(ans, t);
    }
    if (ans == INF)
        printf("-1\n");
    else
        printf("%d\n", ans);
}

int main()
{
    while (~scanf("%d%lld", &S, &M))
        solve(S, M);
    return 0;
}