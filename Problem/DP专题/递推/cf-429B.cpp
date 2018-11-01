// 先预处理出每个格子到四个角落格子的路径最大数值
// 然后枚举两个人相遇的交点格子
// 枚举A,B的进来和出去方式
// 求最大值即可
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
#define LL long long
#define INF (1<<25)
#define MAXN 1010
int mp[MAXN][MAXN];
int dp[5][MAXN][MAXN];
int n,m;

int main()
{
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        memset(mp,0,sizeof(mp));
        memset(dp,0,sizeof(dp));
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);

        // 1 3
        // 2 4
        for (int i=1;i<=n;i++)
        {
            for (int j=1;j<=m;j++)
                dp[1][i][j]=max(dp[1][i-1][j],dp[1][i][j-1])+mp[i][j];
            for (int j=m;j>=1;j--)
                dp[3][i][j]=max(dp[3][i-1][j],dp[3][i][j+1])+mp[i][j];
        }

        for (int i=n;i>=1;i--)
        {
            for (int j=1;j<=m;j++)
                dp[2][i][j]=max(dp[2][i+1][j],dp[2][i][j-1])+mp[i][j];
            for (int j=m;j>=1;j--)
                dp[4][i][j]=max(dp[4][i+1][j],dp[4][i][j+1])+mp[i][j];
        }

        for (int k=1;k<=4;k++)
        {
            for (int i=0;i<=n+1;i++)
                dp[k][i][m+1]=dp[k][i][0]=-INF;
            for (int i=0;i<=m+1;i++)
                dp[k][0][i]=dp[k][n+1][i]=-INF;
        }

        LL ans=0,temp=0;;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
            {
                temp=dp[1][i-1][j]+dp[4][i+1][j]+dp[2][i][j-1]+dp[3][i][j+1];
                ans=max(ans,temp);
                temp=dp[1][i][j-1]+dp[4][i][j+1]+dp[2][i+1][j]+dp[3][i-1][j]; 
                ans=max(ans,temp);
            }

        cout << ans << endl;
    }
    return 0;
}