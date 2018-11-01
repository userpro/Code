#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define LL long long
#define MAXN 50
LL dp[MAXN];
int n,a;

void _init()
{
    memset(dp,0,sizeof(dp));
    dp[1]=dp[2]=1;
    for (int i=3;i<=MAXN;i++)
        dp[i]=dp[i-1]+dp[i-2];
}

int main()
{
    _init();
    while (scanf("%d",&n)!=EOF)
    {
        for (int i=0;i<n;i++)
        {
            scanf("%d",&a);
            printf("%lld\n", dp[a]);
        }
    }
    return 0;
}