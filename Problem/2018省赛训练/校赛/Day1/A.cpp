#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
#define LL long long
LL n,t;

int main()
{
    while (scanf("%lld",&t)!=EOF)
    {
        for (int ii=1;ii<=t;ii++)
        {
            scanf("%lld",&n);
            LL ans=n;
            ans-=(int)sqrt(n);
            ans-=(int)sqrt(n/2);
            printf("Case %d: %lld\n", ii, ans);
        }
    }
    return 0;
}