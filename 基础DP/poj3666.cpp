//用dp[i][j]表示：前i个数构成的序列，这个序列最大值为j，dp[i][j]的值代表相应的cost。
//离散化
//dp[i][j]=abs(j-w[i])+min(dp[i-1][k]);(k<=j)
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define INF 1<<20
#define maxn 2010
int n,a[maxn],b[maxn];
int dp[2][maxn];

void solve()
{
    int mn=0;
    for (int i = 1; i <= n; ++i)
    {
        mn=dp[(i-1)&1][1];
        for (int j = 1; j <= n; ++j)
        {
            mn=min(mn,dp[(i-1)&1][j]);
            dp[i&1][j]=abs(b[j]-a[i])+mn;
        }
    }
    int ans=dp[n&1][1];
    for (int i = 1; i <= n; ++i)
        ans=min(ans,dp[n&1][i]);
    printf("%d\n", ans);
}

int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    memset(dp,0,sizeof(dp));
    solve();
    return 0;
}