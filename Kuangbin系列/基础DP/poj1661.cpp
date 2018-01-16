#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
#define INF 1<<29
struct Node
{
    int x1,x2,high;
}node[MAXN];
int T,N,X,Y,MAXH;
int dp[MAXN][2]; // 0->left 1->right

bool cmp(Node n1,Node n2)
{
    return n1.high<n2.high;
}

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d%d%d%d",&N,&X,&Y,&MAXH);
        for (int i = 1; i <= N; ++i)
            scanf("%d%d%d",&node[i].x1,&node[i].x2,&node[i].high);
        node[0].x1=-20000; node[0].x2=20000; node[0].high=0;
        node[N+1].x1=node[N+1].x2=X; node[N+1].high=Y;
        sort(node,node+N+2,cmp);
        int k;
        for (int i = 1; i <= N+1; ++i)
        {
            // left
            k=i-1;
            while(k > 0 && node[i].high - node[k].high <= MAXH)
            {
                if (node[i].x1 >= node[k].x1 && node[i].x1 <= node[k].x2)
                {
                    dp[i][0]=node[i].high-node[k].high+
                    min(node[i].x1-node[k].x1+dp[k][0],node[k].x2-node[i].x1+dp[k][1]);
                    goto next1;
                }
                k--;
            }
            if (node[i].high - node[k].high > MAXH)
                dp[i][0]=INF;
            else
                dp[i][0]=node[i].high;

            // right
            next1:;
            k=i-1;
            while (k > 0 && node[i].high - node[k].high <= MAXH)
            {
                if (node[i].x2 >= node[k].x1 && node[i].x2 <= node[k].x2)
                {
                    dp[i][1]=node[i].high-node[k].high+
                    min(node[i].x2-node[k].x1+dp[k][0],node[k].x2-node[i].x2+dp[k][1]);
                    goto next2;
                }
                k--;
            }
            if (node[i].high - node[k].high > MAXH)
                dp[i][1]=INF;
            else
                dp[i][1]=node[i].high;
            next2:;
        }
        printf("%d\n", min(dp[N+1][0],dp[N+1][1]));
    }
    return 0;
}