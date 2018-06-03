#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAX 110
int N;
int val[MAX];
vector<int> G[MAX];
bool vis[MAX][MAX];
int fav[MAX];

bool dfs(int bg,int u,int ed)
{
    vis[bg][u]=1;
    if (u==ed) return true;
    int len=G[u].size();
    for (int i=0;i<len;i++)
    {
        int v=G[u][i];
        if (!vis[bg][v])
            if (dfs(bg,v,ed)) return true;
    }
    return false;
}

int main()
{
    while (scanf("%d",&N)!=EOF)
    {
        for (int i=1;i<=N;i++)
            scanf("%d",&val[i]);
        for (int i=1;i<=N;i++)
            scanf("%d",&fav[i]);

        CLR(vis,0);
        for (int i=0;i<MAX;i++)
            G[i].clear();
        for (int i=1;i<=N;i++)
        {
            if (i+fav[i]<=N)
            {
                G[i].push_back(i+fav[i]);
                G[i+fav[i]].push_back(i);
            }
            if (i-fav[i]>=1)
            {
                G[i].push_back(i-fav[i]);
                G[i-fav[i]].push_back(i);
            }
        }

        bool flag=true;
        for (int i=1;i<=N;i++)
            if (!dfs(i,i,val[i]))
            {
                flag=false;
                break;
            }

        if (flag)
            printf("Yes\n");
        else
            printf("No\n");
    }
        
    return 0;
}