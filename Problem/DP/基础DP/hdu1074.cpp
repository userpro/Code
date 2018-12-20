#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define INF 1<<29
#define MAXN 16
struct Node
{
    char str[110];
    int d,c;
}node[MAXN];
int pre[1<<MAXN],dp[1<<MAXN];
int T,N;

void out(int status)
{
    if (status==0) return;
    int t=0;
    for (int i = 0; i < N; ++i)
    {
        if ((status&(1<<i))!=0 && (pre[status]&(1<<i))==0)
        {
            t=i;
            break;
        }
    }
    out(pre[status]);
    printf("%s\n", node[t].str);
}

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d",&N);
        for (int i = 0; i < (1<<N); ++i)
            dp[i]=INF;
        dp[0]=0;
        for (int i = 0; i < N; ++i)
            scanf("%s%d%d",node[i].str,&node[i].d,&node[i].c);
        for (int i = 0; i < (1<<N); ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (i&(1<<j)) continue;
                int s=0;
                for (int k = 0; k < N; ++k)
                    if (i&(1<<k))
                        s+=node[k].c;
                s+=node[j].c;
                if (s>node[j].d) s-=node[j].d;
                else s=0;
                if (dp[i]+s<dp[i|(1<<j)])
                {
                    dp[i|(1<<j)]=dp[i]+s;
                    pre[i|(1<<j)]=i;
                }
            }
        }

        printf("%d\n", dp[(1<<N)-1]);
        out((1<<N)-1);
    }
    return 0;
}