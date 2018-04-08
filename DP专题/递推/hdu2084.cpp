#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
#define LL long long
#define MAXN 110
int t,n;
int mp[MAXN][MAXN];
int dp[MAXN][MAXN];

int main()
{
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        memset(mp,0,sizeof(mp));
        memset(dp,0,sizeof(dp));
        for (int i=1;i<=n;i++)
            for (int j=1;j<=i;j++)
                scanf("%d",&mp[i][j]);

        for (int i=1;i<=n;i++)
            for (int j=1;j<=i;j++)
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-1])+mp[i][j];

        int ans=0;
        for (int i=1;i<=n;i++)
            if (ans<dp[n][i])
                ans=dp[n][i];
        printf("%d\n", ans);
    }
    return 0;
}
