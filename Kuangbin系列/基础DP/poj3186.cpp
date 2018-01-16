//dp，要从内向外推，dp[i][j]表示串中只剩下i~j数的时候最大价值
//dp[i][j]=max(dp[i+1][j]+a[i]*cnt,dp[i][j-1]+a[j]*cnt),因为dp[i][j]时要用到
//后面的数，要从近距离到远距离dp。当然也可以从前向后。
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 2010
int N,val[MAXN],dp[MAXN][MAXN];

int main()
{
    while (scanf("%d",&N)==1)
    {
        memset(dp,0,sizeof(dp));
        for (int i = 1; i <= N; ++i)
        {
            scanf("%d",&val[i]);
            dp[i][i]=val[i];
        }
        for (int i = N; i >= 0; --i)
            for (int j = i; j <= N; ++j)
                dp[i][j]=max(dp[i+1][j]+val[i]*(N-j+i),dp[i][j-1]+val[j]*(N-j+i));
        printf("%d\n", dp[1][N]);
    }
    return 0;
}