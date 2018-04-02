#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 20
int f[MAXN];
int cnt[MAXN];
double c1[MAXN],c2[MAXN];
int n,m;

void fac()
{
    f[0]=1;
    f[1]=1;
    for (int i=2;i<=20;i++)
        f[i]=f[i-1]*i;
}

int main()
{
    fac();
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        memset(cnt,0,sizeof(cnt));
        memset(c1,0,sizeof(c1));
        memset(c2,0,sizeof(c2));
        for (int i=0;i<n;i++)
            scanf("%d",&cnt[i]);

        for (int i=0;i<=cnt[0];i++)
            c1[i]=1.0/f[i];

        for (int i=1;i<n;i++)
        {
            for (int j=0;j<=m;j++)
                for (int k=0;k+j<=m&&k<=cnt[i];k++)
                    c2[k+j]+=c1[j]/f[k];

            memcpy(c1,c2,sizeof(c1));
            memset(c2,0,sizeof(c2));
        }
        printf("%.0lf\n", c1[m]*f[m]);
    }
    return 0;
}