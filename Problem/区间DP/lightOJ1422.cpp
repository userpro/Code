// 如果第i件不能重复利用 dp[i][j]=dp[i+1][j]+1;
// 如果在i+1到j中 有和第i件相同的衣服 是否要重复利用 dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]);
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 110
int dp[MAXN][MAXN],cloth[MAXN];
int T,N,ci;
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        for (int Case=1;Case<=T;Case++)
        {
            scanf("%d",&N);
            for (int i=1;i<=N;i++)
                scanf("%d",&cloth[i]);

            for (int i=1;i<=N;i++)
                for (int j=1;j<=N;j++)
                    dp[i][j]=j-i+1;

            // 方式一
            // for (int i=N-1;i>=1;i--)
            //     for (int j=i+1;j<=N;j++)
            //     {
            //         dp[i][j]=dp[i+1][j]+1;
            //         for (int k=i+1;k<=j;k++)
            //             if (cloth[i]==cloth[k])
            //                 dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]);
            //     }

            // 方式二
            for (int l=1;l<=N;l++)
                for (int i=1;i+l<=N;i++)
                {
                    int j=i+l;
                    dp[i][j]=dp[i+1][j]+1;
                    for (int k=i+1;k<=j;k++)
                        if (cloth[k]==cloth[i])
                            dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]);
                }

            printf("Case %d: %d\n", Case,dp[1][N]);
        }
    }
    return 0;
}