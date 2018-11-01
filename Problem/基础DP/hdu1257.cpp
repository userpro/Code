#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
#define mem(a,b) (memset(a,b,sizeof(a)))
#define MAXN 30010
int N;
int a[MAXN],dp[MAXN];

int main()
{
    while (~scanf("%d",&N))
    {
        mem(dp,0);
        for (int i = 1; i <= N; ++i)
            scanf("%d",&a[i]);
        dp[0]=1;
        for (int i = 1; i <= N; ++i)
        {
            dp[i]=1;
            for (int j = 1; j < i; ++j)
            {
                if (a[i]>a[j])
                    dp[i]=max(dp[i],dp[j]+1);
            }
        }
        int ans=0;
        for (int i = 1; i <= N; ++i)
        {
            if (ans<dp[i])
                ans=dp[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}