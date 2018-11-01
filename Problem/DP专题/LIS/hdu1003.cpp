#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 100010
int num[MAXN];
int T,N;

int main()
{
    scanf("%d",&T);
    int flag=0;
    for (int ii=1;ii<=T;ii++)
    {
        if (flag++) printf("\n");
        printf("Case %d:\n", ii);
        scanf("%d",&N);
        for (int i=1;i<=N;i++)
            scanf("%d",&num[i]);

        int sum=0,mmax=0;
        int cnt=0,start=1,end=1,tmp=1;
        mmax=num[1];
        for (int i=1;i<=N;i++)
        {
            sum+=num[i];
            if (mmax<sum)
            {
                start=tmp;
                end=i;
                mmax=sum;
            }
            if (sum<0)
            {
                tmp=i+1;
                sum=0;
            }
        }
        printf("%d %d %d\n", mmax,start,end);
    }
    return 0;
}