// 当j<n的时候
// dp[i+1][j]+=dp[i][j]*0.5
// dp[i+1][j+1]+=dp[i][j]*0.5

// 当j=n的时候
// dp[i+1][j+1]+=dp[i][j]*0.5
// dp[i+1][j-1]+=dp[i][j]*0.5
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAX 410
double dp[MAX][MAX];
int N,K;
int main()
{
    while (scanf("%d%d",&N,&K)!=EOF)
    {
        CLR(dp,0);
        dp[0][0]=1;
        for (int i=0;i<K;i++)
        {
            for (int j=0;j<=N;j++)
            {
                if (j<N)
                {
                    dp[i+1][j]+=dp[i][j]*0.5;
                    dp[i+1][j+1]+=dp[i][j]*0.5;
                }
                else if (j==N)
                {
                    dp[i+1][j-1]+=dp[i][j]*0.5;
                    dp[i+1][j]+=dp[i][j]*0.5;
                }
            }
        }

        double ans=0;
        for (int i=0;i<=N;i++) // 求期望
            ans+=(dp[K][i]*i);
        printf("%f\n", ans);
    }
    return 0;
}