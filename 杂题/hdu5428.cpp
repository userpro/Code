#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define LL long long
const int maxn=1e6+10;
int t,n;
LL fac[maxn];

int main()
{
    scanf("%d",&t);
    while (t--)
    {
        LL a;
        int cnt=0;
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld",&a);
            for (LL j = 2; j*j <= a; ++j)
            {
                while (a%j==0)
                {
                    fac[cnt++]=j;
                    a/=j;
                }
            }
            if (a>1) fac[cnt++]=a;
        }
        if (cnt<2)
            printf("-1\n");
        else {
            sort(fac,fac+cnt);
            printf("%lld\n", fac[0]*fac[1]);
        }
    }
    return 0;
}