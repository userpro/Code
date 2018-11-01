#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define LL long long
#define MAXN 60
LL dp[MAXN];
int n,a,b;

void _init()
{
    memset(dp,0,sizeof(dp));
    dp[0]=dp[1]=1;
    for (int i=2;i<=MAXN;i++)
        dp[i]=dp[i-1]+dp[i-2];
}

int main()
{
    _init();
    while (scanf("%d",&n)!=EOF)
    {
        for (int i=0;i<n;i++)
        {
            scanf("%d%d",&a,&b);
            printf("%lld\n", dp[b-a]);
        }
    }
    return 0;
}