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
char s1[MAXN],s2[MAXN];
int dp[MAXN][MAXN],ans[MAXN];
int main()
{
    while (scanf("%s%s",s1+1,s2+1)!=EOF)
    {
        int len=strlen(s1+1);
        CLR(dp,0);
        for (int i=1;i<=len;i++)
            dp[i][i]=1;
        for (int l=1;l<=len;l++)
            for (int i=1;i+l<=len;i++)
            {
                int j=i+l;
                dp[i][j]=dp[i+1][j]+1; // 只比较第i位和第k位
                for (int k=i+1;k<=j;k++)
                    if (s2[i]==s2[k]) // 出现分割点 分割子问题
                        dp[i][j]=min(dp[i][j],dp[i+1][k]+dp[k+1][j]);
            }

        CLR(ans,0);
        for (int i=1;i<=len;i++)
            ans[i]=dp[1][i];
        for (int i=1;i<=len;i++)
        {
            if (s1[i]==s2[i]) // 少刷一次
                ans[i]=ans[i-1];
            else
            {
                for (int j=1;j<i;j++) // 寻找最小子问题
                    ans[i]=min(ans[i],ans[j]+dp[j+1][i]);
            }
        }
        printf("%d\n", ans[len]);
    }
    return 0;
}