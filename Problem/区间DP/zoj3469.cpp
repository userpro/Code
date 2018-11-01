// 用dp[i][j][0]表示访问完区间[i,j]并留在左端点, dp[i][j][1]表示访问完区间[i,j]并留在右端点.
// 把饭店那个地方也加进去作为点. 从饭店那个点往两边进行DP;
// dp[i][j][0] 可以根据dp[i+1][j][0]和dp[i+1][j][1]得到.
// dp[i][j][1] 可以根据dp[i][j-1][0]和dp[i][j-1][1]得到.
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 1010
struct Node
{
    int x,b;
} nodes[MAXN];
int sum[MAXN];
int dp[MAXN][MAXN][2];
int N,V,X;

bool cmp(const Node& n1,const Node& n2)
{
    if (n1.x==n2.x) return n1.b<n2.b;
    return n1.x<n2.x;
}

int main()
{
    while (scanf("%d%d%d",&N,&V,&X)!=EOF)
    {
        for (int i=1;i<=N;i++)
            scanf("%d%d",&nodes[i].x,&nodes[i].b);
        N++;
        nodes[N].x=X;
        nodes[N].b=0;
        sort(nodes+1,nodes+N+1,cmp);
        sum[0]=0;
        for (int i=1;i<=N;i++)
            sum[i]=sum[i-1]+nodes[i].b;
        int st=0;
        for (int i=1;i<=N;i++)
            if (nodes[i].x==X)
            {
                st=i;
                break;
            }

        for (int i=1;i<=N;i++)
            for (int j=1;j<=N;j++)
                dp[i][j][0]=dp[i][j][1]=INF;
        dp[st][st][0]=dp[st][st][1]=0;

        for (int i=st;i>=1;i--)
            for (int j=st;j<=N;j++)
            {
                if (i==j) continue;
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][0]+(sum[i]+sum[N]-sum[j])*(nodes[i+1].x-nodes[i].x));
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][1]+(sum[i]+sum[N]-sum[j])*(nodes[j].x-nodes[i].x));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][0]+(sum[i-1]+sum[N]-sum[j-1])*(nodes[j].x-nodes[i].x));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][1]+(sum[i-1]+sum[N]-sum[j-1])*(nodes[j].x-nodes[j-1].x));
            }

        printf("%d\n", V*min(dp[1][N][0],dp[1][N][1]));
    }
    return 0;
}