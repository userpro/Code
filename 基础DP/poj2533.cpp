#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
int N;
int dp[MAXN],a[MAXN];

int main()
{
    while (~scanf("%d",&N))
    {
        for (int i = 1; i <= N; ++i)
            scanf("%d",&a[i]);
        for (int i = 1; i <= N; ++i)
            dp[i]=1;
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j < i; ++j)
            {
                if (a[j]<a[i])
                    dp[i]=max(dp[i],dp[j]+1);
            }
        }
        int ans=-1;
        for (int i = 1; i <= N; ++i)
        {
            if (ans<dp[i])
                ans=dp[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}