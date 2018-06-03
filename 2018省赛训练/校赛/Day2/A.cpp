#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 100010
int sum[MAXN];
int num[MAXN];
int n,k;

int main()
{
    while (scanf("%d%d",&n,&k)!=EOF)
    {
        for (int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        int a;
        int mm=0;
        memset(sum,0,sizeof(sum));
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&a);
            if (a==0)
                sum[i]=sum[i-1]+num[i];
            else
            {
                mm+=num[i];
                sum[i]=sum[i-1];
            }
        }
        int mmax=0;
        for (int i=k;i<=n;i++)
        {
            int tmp=sum[i]-sum[i-k];
            if (mmax<tmp)
                mmax=tmp;
        }

        printf("%d\n", mmax+mm);
    }
    return 0;
}