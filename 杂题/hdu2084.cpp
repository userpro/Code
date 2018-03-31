#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 110
#define max(a,b) (a>b?a:b)
int dp[MAXN][MAXN],V[MAXN][MAXN];
int T,N;

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d",&N);
        memset(dp,-1,sizeof(dp));
        memset(V,0,sizeof(V));
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= i; ++j)
                scanf("%d",&V[i][j]);

        dp[0][0]=V[1][0];
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= i; ++j)
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-1])+V[i][j];

        int ans=0;
        for (int i = 1; i <= N; ++i)
            if (ans<dp[N][i])
                ans=dp[N][i];
        printf("%d\n",ans);
    }
    return 0;
}