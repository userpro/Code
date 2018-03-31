#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxm=1e4+10;
const int maxn=1e6+10;
int t,n,m;
int a[maxn],b[maxm],nx[maxm];

void kmp_pre(int x[],int m,int nx[])
{
    int i,j;
    j=nx[0]=-1;
    i=0;
    while (i<m)
    {
        while (j!=-1 && x[i]!=x[j]) j=nx[j];
        nx[++i]=++j;
    }
}

int main()
{
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++i)
            scanf("%d",&a[i]);
        for (int i = 0; i < m; ++i)
            scanf("%d",&b[i]);
        kmp_pre(b,m,nx);
        int x,y,ans=-1;
        x=y=0;
        while (x<n)
        {
            while (y!=-1 && a[x]!=b[y]) y=nx[y];
            x++; y++;
            if (y>=m)
            {
                ans=x;
                break;
            }
        }
        printf("%d\n", ans==-1?-1:ans-m+1);
    }
    return 0;
}