#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 100010
double sum[2*MAXN];
int n,k;

int main()
{
    while (scanf("%d%d",&n,&k)!=EOF)
    {
        sum[0]=0;
        for (int i=1;i<=n;i++)
        {
            scanf("%lf",&sum[i]);
            sum[i]+=sum[i-1];
        }
        double ans=0;
        double t=n-k+1;
        for (int i=1;i<=n-k+1;i++)
            ans+=(sum[i+k-1]-sum[i-1])/t;
        if (!ans)
            ans=sum[1];
        printf("%.10f\n", ans);
    }
    return 0;
}