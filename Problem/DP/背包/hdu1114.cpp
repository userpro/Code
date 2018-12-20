// 完全背包
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 510
#define MAXC 10010
#define INF 0x3f3f3f3f
int f[MAXC],P[MAXC],W[MAXC];
int T,E,F,N;

int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            scanf("%d%d%d",&E,&F,&N);
            int V=F-E;
            for (int i=1;i<=N;i++)
                scanf("%d%d",&P[i],&W[i]);

            memset(f,0x3f,sizeof(f));
            f[0]=0;
            for (int i=1;i<=N;i++)
                for (int j=W[i];j<=V;j++)
                    f[j]=min(f[j],f[j-W[i]]+P[i]);

            if (f[V]==INF)
                printf("This is impossible.\n");
            else
                printf("The minimum amount of money in the piggy-bank is %d.\n", f[V]);
        }
    }
    return 0;
}