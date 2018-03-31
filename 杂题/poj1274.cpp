#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn=210;
int m,n;
int uN,vN;
int G[maxn][maxn];
int linker[maxn];
bool vis[maxn];

bool dfs(int u)
{
    for (int v = 1; v <= vN; ++v)
    {
        if (G[u][v]&&!vis[v])
        {
            vis[v]=1;
            if (linker[v]==-1 || dfs(linker[v]))
            {
                linker[v]=u;
                return true;
            }
        }
    }
    return false;
}

int hungray()
{
    int res=0;
    memset(linker,-1,sizeof(linker));
    for (int u = 1; u <= uN; ++u)
    {
        memset(vis,0,sizeof(vis));
        if (dfs(u)) res++;
    }
    return res;
}

int main()
{
    while (scanf("%d%d",&n,&m) != EOF)
    {
        uN=n;
        vN=m;
        memset(G,0,sizeof(G));
        int num,v;
        for (int u = 1; u <= n; ++u)
        {
            scanf("%d",&num);
            for (int j = 0; j < num; ++j)
            {
                scanf("%d",&v);
                G[u][v]=1;
            }
        }
        printf("%d\n", hungray());
    }
    return 0;
}