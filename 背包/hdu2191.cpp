// 多重背包
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 110
int f[MAXN];
int C[MAXN],W[MAXN],cnt[MAXN];
int T,N,M;

int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        scanf("%d%d",&N,&M);
        for (int i=1;i<=M;i++)
            scanf("%d%d%d",&C[i],&W[i],&cnt[i]);
        memset(f,0,sizeof(f));
        for (int i=1;i<=M;i++)
            for (int j=0;j<=cnt[i];j++)
                for (int k=N;k>=C[i];k--)
                    f[k]=max(f[k],f[k-C[i]]+W[i]);

        int ans=0;
        for (int i=0;i<=N;i++)
            ans=max(ans,f[i]);
        printf("%d\n", ans);
    }
    return 0;
}