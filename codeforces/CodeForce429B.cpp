#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define mem(a,b) (memset(a,b,sizeof(a)))
#define MAXN 1010
int n,m;
int val[MAXN][MAXN];
long long dp[MAXN][MAXN][4];

int main()
{
    while (scanf("%d%d",&n,&m)==2)
    {
        mem(val,0);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                scanf("%d",&val[i][j]);

        mem(dp,0);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                dp[i][j][0]=max(dp[i-1][j][0],dp[i][j-1][0])+val[i][j];
        for (int i = 1; i <= n; ++i)
            for (int j = m; j > 0; --j)
                dp[i][j][1]=max(dp[i-1][j][1],dp[i][j+1][1])+val[i][j];
        for (int i = n; i > 0; --i)
            for (int j = m; j > 0; --j)
                dp[i][j][2]=max(dp[i+1][j][2],dp[i][j+1][2])+val[i][j];
        for (int i = n; i > 0; --i)
            for (int j = 0; j <= m; ++j)
                dp[i][j][3]=max(dp[i+1][j][3],dp[i][j-1][3])+val[i][j];
        
        long long ans=0;
        for (int i = 2; i < n; ++i)
            for (int j = 2; j < m; ++j)
            {
                ans=max(ans,dp[i][j-1][0]+dp[i][j+1][2]+dp[i-1][j][1]+dp[i+1][j][3]);
                ans=max(ans, dp[i][j-1][3]+dp[i][j+1][1]+dp[i-1][j][0]+dp[i+1][j][2]);
            }
        printf("%lld\n", ans);
    }
    return 0;
}