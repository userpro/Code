#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
#define INF (1<<20)
int num[MAXN];
int n,m,a;

int main()
{
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        memset(num,0,sizeof(num));
        for (int i=1;i<=m;i++)
        {
            scanf("%d",&a);
            num[a]++;
        }
        int mmin=INF;
        for (int i=1;i<=n;i++)
        {
            if (mmin>num[i])
                mmin=num[i];
        }
        printf("%d\n", mmin);
    }
    return 0;
}