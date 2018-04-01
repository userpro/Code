// 01背包
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
int f[MAXN],C[MAXN],W[MAXN];
int T,n,v;

int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            scanf("%d%d",&n,&v);
            for (int i=1;i<=n;i++)
                scanf("%d",&W[i]);

            for (int i=1;i<=n;i++)
                scanf("%d",&C[i]);

            memset(f,0,sizeof(f));
            for (int i=1;i<=n;i++)
                for (int j=v;j>=C[i];j--)
                    f[j]=max(f[j],f[j-C[i]]+W[i]);

            int ans=0;
            for (int i=0;i<=v;i++)
                ans=max(ans,f[i]);
            printf("%d\n", ans);
        }
    }
    return 0;
}