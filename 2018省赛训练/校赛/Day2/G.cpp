#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define INF (1<<25)
#define MAXN 1010
int num[MAXN];
int n,m;

int main()
{
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        int a;
        memset(num,0,sizeof(num));
        for (int i=1;i<=m;i++)
        {
            scanf("%d",&a);
            num[a]++;
        }
        int mmin=INF;
        for (int i=1;i<=n;i++)
            mmin=min(mmin,num[i]);
        if (mmin==INF)
            mmin=0;
        printf("%d\n", mmin);
    }
    return 0;
}