#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
#define INF (1<<25)
int num[MAXN];
int lis[MAXN];
int n;

int main()
{
    while (scanf("%d",&n)!=EOF&&n)
    {
        memset(lis,0,sizeof(lis));
        for (int i=0;i<n;i++)
            scanf("%d",&num[i]);
        int ans=-INF;
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<i;j++)
                if (num[j]<num[i])
                    lis[i]=max(lis[i],lis[j]);
            lis[i]+=num[i];
            if (ans<lis[i])
                ans=lis[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}