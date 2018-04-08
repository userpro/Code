// 二分图匹配
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
const int INF=1<<29;
const int maxn=1010;
int k,m,n;
int uN,vN;
vector<int> G[maxn];
int mx[maxn],my[maxn];
int dx[maxn],dy[maxn];
int dis;
bool vis[maxn];

bool SearchP()
{
    queue<int> Q;
    dis=INF;
    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for (int i = 1; i <= uN; ++i)
    {
        if (mx[i]==-1)
        {
            Q.push(i);
            dx[i]=0;
        }
    }
    while (!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        if (dx[u]>dis) break;
        int sz=G[u].size();
        for (int i = 0; i < sz; ++i)
        {
            int v=G[u][i];
            if (dy[v]==-1)
            {
                dy[v]=dx[u]+1;
                if (my[v]==-1)
                    dis=dy[v];
                else {
                    dx[my[v]]=dy[v]+1;
                    Q.push(my[v]);
                }
            }
        }
    }
    return dis!=INF;
}

bool dfs(int u)
{
    int sz=G[u].size();
    for (int i = 0; i < sz; ++i)
    {
        int v=G[u][i];
        if (!vis[v] && dy[v]==dx[u]+1)
        {
            vis[v]=1;
            if (my[v]!=-1 && dy[v]==dis) continue;
            if (my[v]==-1 || dfs(my[v]))
            {
                my[v]=u;
                mx[u]=v;
                return true;
            }
        }
    }
    return false;
}

int MaxMatch()
{
    int ans=0;
    memset(mx,-1,sizeof(mx));
    memset(my,-1,sizeof(my));
    while (SearchP())
    {
        memset(vis,0,sizeof(vis));
        for (int i = 1; i <= uN; ++i)
        {
            if (mx[i]==-1 && dfs(i))
                ans++;
        }
    }
    return ans;
}

int main()
{
    while (scanf("%d%d%d",&k,&m,&n)==3&&k)
    {
        memset(G,0,sizeof(G));
        uN=m; vN=n;
        int x,y;
        for (int i = 0; i < k; ++i)
        {
            scanf("%d%d",&x,&y);
            G[x].push_back(y);
        }
        printf("%d\n", MaxMatch());
    }
    return 0;
}