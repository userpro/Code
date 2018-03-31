#include <cstdio>
#include <cstring>

using namespace std;
#define MAXN 10010
int c1[MAXN], c2[MAXN];
int num[110], ans[110];
int n,mmax;

int main()
{
    while (scanf("%d",&n)!=EOF)
    {
        memset(c1,0,sizeof(c1));
        memset(c2,0,sizeof(c2));
        mmax=0;
        for (int i=0;i<n;i++)
        {
            scanf("%d",&num[i]);
            mmax+=num[i];
        }

        for (int i=0;i<=num[0];i+=num[0])
            c1[i]=1;

        for (int i=1;i<n;i++)
        {
            for (int j=0;j<=mmax;j++)
                for (int k=0;k+j<=mmax && k<=num[i];k+=num[i])
                {
                    if (k>=j) c2[k-j]+=c1[j];
                    else c2[j-k]+=c1[j];
                    c2[k+j]+=c1[j];
                }

            memcpy(c1,c2,sizeof(c1));
            memset(c2,0,sizeof(c2));
        }

        int x=0;
        for (int i=0;i<=mmax;i++)
            if (!c1[i])
                ans[x++]=i;

        printf("%d\n", x);
        for (int i=0;i<x;i++)
            if (i!=x-1)
                printf("%d ", ans[i]);
            else
                printf("%d\n", ans[i]);
    }
    return 0;
}