// codeforces 1027E dp+组合数学
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const long long mod=998244353;
int n,k;
long long dp[510][510];
int main() {
    while (~scanf("%d%d",&n,&k)) {
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for (int i=1;i<=n;i++) {
            for (int j=1;j<=i;j++)
                for (int k=1;k<=j;k++)
                    if (i-k>=0) dp[i][j]=(dp[i][j]+dp[i-k][min(j,i-k)])%mod;
        }
        for (int i=n;i>=1;i--) dp[n][i]=(dp[n][i]-dp[n][i-1]+mod)%mod;
        long long ans=0;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n && i*j<k;j++)
                ans=(ans+dp[n][i]*dp[n][j]%mod)%mod;
        printf("%I64d\n", ans*2%mod);
    }
    return 0;
}