#include <cstdio>
#include <cstring>

using namespace std;
#define MAXN 250010
int n,v,m;
int c1[MAXN],c2[MAXN];
int val[55], cnt[55];
int mmax;

int main()
{
    while (scanf("%d",&n) != EOF && n > 0)
    {
        memset(c1,0,sizeof(c1));
        memset(c2,0,sizeof(c2));
        for (int i=0;i<n;i++)
            scanf("%d%d",&val[i],&cnt[i]);

        mmax=0;
        for (int i=0;i<n;i++)
            mmax+=val[i]*cnt[i];

        for (int i=0;i<=cnt[0]*val[0];i+=val[0])
            c1[i]=1;

        int len=val[0]*cnt[0];
        for (int i=1;i<n;i++)
        {
            for (int j=0;j<=len;j++)
                if (c1[j]!=0)
                    for (int k=0;k<=val[i]*cnt[i];k+=val[i])
                        if (k+j<=mmax)
                            c2[k+j]+=c1[j];

            len+=val[i]*cnt[i];
            memcpy(c1,c2,sizeof(c1));
            memset(c2,0,sizeof(c2));
        }

        int i;
        for (i=mmax/2;i>=0;i--)
            if (c1[i]!=0)
                break;

        printf("%d %d\n", mmax-i, i);
    }
    return 0;
}