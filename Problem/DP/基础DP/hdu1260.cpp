#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define mem(a,b) (memset(a,b,sizeof(a)))
#define MAXN 2010
int N,K;
int a[MAXN],b[MAXN],dp[MAXN];

int main()
{
    scanf("%d",&N);
    while (N--)
    {
        mem(a,0); mem(b,0); mem(dp,0);
        scanf("%d",&K);
        for (int i = 1; i <= K; ++i)
            scanf("%d",&a[i]);
        for (int i = 1; i <= K-1; ++i)
            scanf("%d",&b[i]);
        dp[1]=a[1]; dp[2]=min(dp[1]+a[2],b[1]);
        for (int i = 3; i <= K; ++i)
        {
            dp[i]=min(dp[i-1]+a[i],dp[i-2]+b[i-1]);
        }
        int minutes=(dp[K]/60)%60,seconds=dp[K]%60,hours=dp[K]/3600+8;
        printf("%02d:%02d:%02d %s\n", hours%24,minutes,seconds,hours%24>12?"pm":"am");
    }
    return 0;
}