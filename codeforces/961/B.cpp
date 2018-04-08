#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 100010
int n,k;
int num[MAXN];
int sum[MAXN];

int main()
{
    int a;
    while (scanf("%d%d",&n,&k)!=EOF)
    {
        for (int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        memset(sum,0,sizeof(sum));
        int ans=0;
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&a);
            if (a==0)
                sum[i]=sum[i-1]+num[i];
            else
            {
                sum[i]=sum[i-1];
                ans+=num[i];
            }
        }
        int mmax=0;
        for (int i=k;i<=n;i++)
        {
            if (mmax<sum[i]-sum[i-k])
                mmax=sum[i]-sum[i-k];
        }
        ans+=mmax;
        printf("%d\n", ans);
    }
    return 0;
}