// dp[i][j]=dp[i-1][j-num[i]]+dp[i-1][j+num[i]];
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
#define MOD 1000000007
#define MAXN 1010
int T,n,m,s;
int num[MAXN];
int dp[MAXN][MAXN];

int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            memset(dp,0,sizeof(dp));
            scanf("%d%d%d",&n,&m,&s);
            dp[0][s]=1;
            for (int i=1;i<=m;i++)
                scanf("%d",&num[i]);

            for (int i=1;i<=m;i++)
            {
                for (int j=1;j<=n;j++)
                {
                    int a=j-num[i];
                    int b=j+num[i];
                    if (a>0&&a<=n)
                        dp[i][j]+=dp[i-1][a];
                    if (b>0&&b<=n)
                        dp[i][j]+=dp[i-1][b];
                    dp[i][j]%=MOD;
                }
            }
            for (int i=1;i<=n;i++)
                printf("%d ", dp[m][i]);
            printf("\n");
        }
    }
    return 0; 
}