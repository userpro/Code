#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 200
struct Node
{
    int x,y,z;
}node[MAXN];
int N;
int dp[MAXN];

bool cmp(Node n1, Node n2)
{
    if (n1.x==n2.x)
        return n1.y<n2.y;
    return n1.x<n2.x;
}

int main()
{
    int tot=1;
    while (scanf("%d",&N)==1&&N)
    {
        int inx=0;
        memset(dp,0,sizeof(dp));
        int x,y,z;
        for (int i = 0; i < N; ++i)
        {
            scanf("%d%d%d",&x,&y,&z);
            node[inx].x=x; node[inx].y=y; node[inx].z=z; inx++;
            node[inx].x=x; node[inx].y=z; node[inx].z=y; inx++;
            node[inx].x=y; node[inx].y=z; node[inx].z=x; inx++;
            node[inx].x=y; node[inx].y=x; node[inx].z=z; inx++;
            node[inx].x=z; node[inx].y=x; node[inx].z=y; inx++;
            node[inx].x=z; node[inx].y=y; node[inx].z=x; inx++;
        }
        sort(node,node+inx,cmp);
        dp[0]=node[0].z;
        int mmax=0;
        for (int i = 1; i < inx; ++i)
        {
            mmax=0;
            for (int j = 0; j < i; ++j)
            {
                if (node[j].x<node[i].x && node[j].y<node[i].y)
                    mmax=mmax>dp[j]?mmax:dp[j];
            }
            dp[i]=mmax+node[i].z;
        }

        int ans=0;
        for (int i = 0; i < inx; ++i)
        {
            if (ans<dp[i])
                ans=dp[i];
        }

        printf("Case %d: maximum height = %d\n", tot++, ans);
    }
    return 0;
}