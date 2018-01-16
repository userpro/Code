#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
int N;
int dp[MAXN],V[MAXN];

int main()
{
    while (scanf("%d",&N)==1&&N)
    {
        memset(dp,0,sizeof(dp));
        memset(V,0,sizeof(V));
        for (int i = 0; i < N; ++i)
        {
            scanf("%d",&V[i]);
            dp[i]=V[i];
        }
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < i; ++j)
                if (V[j]<V[i])
                    dp[i]=max(dp[i],dp[j]+V[i]);

        int ans=0;
        for (int i = 0; i < N; ++i)
            if (ans<dp[i])
                ans=dp[i];
        printf("%d\n",ans);
    }
    return 0;
}