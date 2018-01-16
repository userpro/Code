#include <cstdio>
#include <cstring>
#include <cmath>

#define MAXN 1000010
#define INF (1<<29)
#define max(a,b) (a>b?a:b)
int M,N;
int D[MAXN], dp[MAXN], mmax[MAXN];

int main()
{
    while (scanf("%d%d",&M,&N)==2)
    {
        memset(D,0,sizeof(D));
        memset(dp,0,sizeof(dp));
        memset(mmax,0,sizeof(mmax));
        for (int i = 1; i <= N; ++i)
            scanf("%d",&D[i]);

        // dp[i][j]=max(dp[i][j-1]+D[j], max(dp[i-1][k])+D[j])  0<k<j
        int t=0;
        for (int i = 1; i <= M; ++i)
        {
            t=-INF;
            for (int j = i; j <= N; ++j)
            {
                dp[j]=max(dp[j-1]+D[j], mmax[j-1]+D[j]);
                mmax[j-1]=t;
                t=max(t, dp[j]);
            }
        }
        printf("%d\n", t);
    }
    return 0;
}