#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 100010
struct Node
{
    int v,w;
    int next;
} edge[MAXN<<2];
LL head[MAXN];
LL tot;

void add(int u,int v,int w)
{
    edge[tot].w=w; edge[tot].v=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

void _init()
{
    CLR(head,-1);
    tot=0;
}


// int dfs(int u,int fa,int ans)
// {
//     for (int i=head[u];i!=-1;i=edge[i].next)
//     {
//         int w=edge[i].w;
//         int v=edge[i].v;
//         if (fa!=v)
//             dfs(v,u,ans^w)
//     }
//     fa->u=ans
// }


int main()
{
    _init();
    int n, m;
    cin >> n >> m;
    for (int i=0; i<m; i++) {int u, v; LL t;cin >> u >> v >> t;add(min(u, v), max(u, v), t);}
    for (int i=head[u];i!=-1;i=edge[i].next)
        for (int j=edge[i].next, j!=-1; j=edge[j].next) add()
    return 0;
}