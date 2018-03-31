#include <cstdio>
#include <cstring>

#define MAXN 310
int n;
int c1[MAXN], c2[MAXN];

int main()
{
    while (scanf("%d",&n)!=EOF && n)
    {
        for (int i=0;i<=n;i++)
        {
            c1[i]=1;
            c2[i]=0;
        }
        for (int i=2;i<=n && i<=17;i++)
        {
            for (int j=0;j<=n;j++)
                for (int k=0;k+j<=n;k+=i*i)
                    c2[k+j]+=c1[j];

            for (int j=0;j<=n;j++)
            {
                c1[j]=c2[j];
                c2[j]=0;
            }
        }
        printf("%d\n", c1[n]);
    }
    return 0;
}