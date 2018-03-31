/**
0 (1) 1
(3) 2 0 3
(2) 1 3
(3) 1 2 4
(1) 3
(1) 6
(1) 7
(0)
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <cstring>
using namespace std;
#define INF 0xfffffff
#define maxn 11005
#define min(a,b) (a<b?a:b)
/** 无向图求桥 **/struct node
{
    int x, y;
    bool friend operator < (node A,node B)
    {
        if(A.x == B.x)
            return A.y < B.y;
        return A.x < B.x;
    }
}bridge[maxn];
int n, dfn[maxn], low[maxn], Father[maxn], Time;
vector<int> G[maxn];

void init()
{
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(Father, 0, sizeof(Father));
    Time = 0;
    for(int i=0; i<n; i++)
        G[i].clear();
}

void Tarjan(int u,int fa)
{
    Father[u] = fa;
    low[u] = dfn[u] = ++Time;
    int len = G[u].size(), v;

    for(int i=0; i<len; i++)
    {
        v = G[u][i];

        if( !low[v] )
        {
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if(fa != v)
            low[u] = min(low[u], dfn[v]);
    }
}

void solve()
{
    int ans = 0;
    for(int i=0; i<n; i++)
    {
        if(!low[i])
            Tarjan(i, -1);
    }

    for(int i=0; i<n; i++)
    {
        int v = Father[i];
        if(v != -1 && dfn[v] < low[i])
        {

            bridge[ans].x = i;
            bridge[ans].y = v;

            if(bridge[ans].x > bridge[ans].y)
                swap(bridge[ans].x, bridge[ans].y);
            ans ++;
        }
    }
    sort(bridge, bridge + ans);

    printf("%d critical links\n", ans);

    for(int i=0; i<ans; i++)
    {
        printf("%d - %d\n",bridge[i].x,bridge[i].y);
    }
    printf("\n");
}

int main()
{
    while(scanf("%d",&n) != EOF)
    {
        init();
        for(int i=0; i<n; i++)
        {
            int a, b, m;
            scanf("%d (%d)",&a,&m);

            while(m--)
            {
                scanf("%d", &b);
                G[a].push_back(b);
                G[b].push_back(a);
            }
        }
        solve();
    }
    return 0;
}