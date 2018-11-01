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
int T,N;
int dp[MAXN][MAXN],sum[MAXN],a[MAXN];
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        for (int cas=1;cas<=T;cas++)
        {
            scanf("%d",&N);
            sum[0]=0;
            for (int i=1;i<=N;i++)
            {
                scanf("%d",&a[i]);
                sum[i]=sum[i-1]+a[i];
            }

            CLR(dp,0);
            for (int i=1;i<=N;i++)
                for (int j=i+1;j<=N;j++)
                    dp[i][j]=INF;
            for (int l=1;l<=N;l++)
                for (int i=1;i+l<=N;i++)
                {
                    int j=i+l;
                    for (int k=1;k<=j-i+1;k++)
                        dp[i][j]=min(dp[i][j],dp[i+1][i+k-1]+dp[i+k][j]+k*(sum[j]-sum[i+k-1])+(k-1)*a[i]);
                    // dp[i][j] 表示第i到第j个人的区间
                    // 只考虑这个区间内的排名 分两种情况
                    // 1. 第i个人在第1个上 
                    // 2. 第i个人在第k个上 不满意度由四部分组成
                    //      (k-1)*a[i] 当前上去的这个人(即第i个人)
                    //      k*(sum[j]-sum[i-k+1]) 排在这个人之后的所有人的
                    //      dp[i+1][i+k-1]+dp[i+k][j] 分解后的两个子区间(第i个人的情况已经讨论)
                }
            printf("Case #%d: %d\n", cas, dp[1][N]);
        }
    }
    return 0;
}