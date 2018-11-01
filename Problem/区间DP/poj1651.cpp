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
int N;
int num[MAXN],dp[MAXN][MAXN];
int main()
{
    while (scanf("%d",&N)!=EOF)
    {
        for (int i=0;i<N;i++)
            scanf("%d",&num[i]);

        CLR(dp,0);
        for (int l=2;l<N;l++)
            for (int i=1;i+l-1<N;i++)
            {
                int j=l+i-1;
                dp[i][j]=INF;
                for (int k=i;k<j;k++)
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+num[k]*num[i-1]*num[j]);
            }

        printf("%d\n", dp[1][N-1]);
    }
    return 0;
}