#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1100
struct Node
{
    int w,s,ix;
}node[MAXN];
int dp[MAXN],pre[MAXN],path[MAXN];

bool cmp(Node n1,Node n2)
{
    if (n1.w==n2.w)
        return n1.s>n2.s;
    return n1.w<n2.w;
}

int main()
{
    int w,s,inx=1;
    memset(pre,-1,sizeof(pre));
    memset(path,0,sizeof(path));
    while (scanf("%d%d",&w,&s)!=EOF)
    {
        dp[inx]=1;
        node[inx].w=w;
        node[inx].s=s;
        node[inx].ix=inx;
        inx++;
    }
    int n=inx-1;
    sort(node, node+n+1, cmp);

    int ans=0,k=0,cnt=0;
    for (int i=1; i<=n; ++i)
    {
        for (int j=1; j<i; ++j)
        {
            if (node[i].w>node[j].w && node[i].s<node[j].s && dp[i]<dp[j]+1)
            {
                dp[i]=dp[j]+1;
                pre[i]=j;
                if (ans<dp[i])
                {
                    ans=dp[i];
                    k=i;
                }
            }
        }
    }
    while (pre[k]!=-1)
    {
        path[cnt++]=k;
        k=pre[k];
    }
    path[cnt++]=k;
    printf("%d\n", ans);
    for (int i = cnt-1; i >= 0; --i)
        printf("%d\n", node[path[i]].ix);
    return 0;
}