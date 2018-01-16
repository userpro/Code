#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;
#define MAXN 100110
#define max2(a,b) (a>b?a:b)
#define max3(a,b,c) (a>b?a>c?a:c:b>c?b:c)
int N;
int dp[11][MAXN];

// dp[i][j]+=max(dp[i][j-1],dp[i-1][j-1],dp[i+1][j-1])+V[i][j-1])
int main()
{
    while (scanf("%d",&N)==1&&N)
    {
        memset(dp,0,sizeof(dp));
        int x,t,maxt;
        for (int i = 0; i < N; ++i)
        {
            scanf("%d%d",&x,&t);
            dp[x][t]++;
            if (t>maxt)
                maxt=t;
        }
        for (int i = maxt-1; i >= 0; --i)
        {
            dp[0][i]+=max2(dp[0][i+1],dp[1][i+1]);
            dp[10][i]+=max2(dp[10][i+1],dp[9][i+1]);
            for (int j = 1; j < 10; ++j)
                dp[j][i]+=max3(dp[j][i+1],dp[j+1][i+1],dp[j-1][i+1]);
        }

        printf("%d\n", dp[5][0]);
    }
    return 0;
}