#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define INF 1<<28
#define MAXN 510
#define MAXV 10010
int T,E,F,N;
int dp[MAXV];
int val[MAXN],cost[MAXN];

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d%d%d",&E,&F,&N);
        int V=F-E;
        dp[0]=0;
        for (int i = 1; i <= V; ++i)
            dp[i]=INF;
        
        for (int i = 0; i < N; ++i)
            scanf("%d%d",&val[i],&cost[i]);

        for (int i = 0; i < N; ++i)
            for (int j = cost[i]; j <= V; ++j)
                dp[j]=min(dp[j-cost[i]]+val[i],dp[j]);
        
        if (dp[V]!=INF)
            printf("The minimum amount of money in the piggy-bank is %d.\n",dp[V]);
        else
            printf("This is impossible.\n");
    }
    return 0;
}