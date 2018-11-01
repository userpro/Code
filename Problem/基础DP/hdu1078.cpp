#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 110
int n,k;
int dp[MAXN][MAXN],a[MAXN][MAXN];
int to[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

int dfs(int x,int y)
{
    if (!dp[x][y])
    {
        int maxx=0;
        for (int i = 1; i <= k; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                int xx=x+to[j][0]*i;
                int yy=y+to[j][1]*i;
                if (xx>=0&&yy>=0&&xx<n&&yy<n&&a[xx][yy]>a[x][y])
                    maxx=max(maxx,dfs(xx,yy));
            }
        }
        dp[x][y]=maxx+a[x][y];
    }
    return dp[x][y];
}

int main()
{
    while (scanf("%d%d",&n,&k)==2&&n!=-1&&k!=-1)
    {
        memset(dp,0,sizeof(dp));
        memset(a,0,sizeof(a));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d",&a[i][j]);
        printf("%d\n", dfs(0,0));
    }
    return 0;
}