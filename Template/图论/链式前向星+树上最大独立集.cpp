// 求树上独立集的最大异或和
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+100;
int t,n;
int dp[maxn][2],f[maxn];
int head[maxn];
int cnt;
struct E
{
    int w,to,next;
}edge[maxn];

void _init()
{
    memset(head,-1,sizeof(head));
    cnt=0;
}

void adde(int u,int v,int w)
{
    edge[cnt].w=w;
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

int solve(int u,int v)
{
    dp[u][0]=f[u];
    dp[u][1]=0;
    for (int i=head[u];i!=-1;i=edge[i].next)
    {
        int to=edge[i].to;
        if (to==v) continue;
        solve(to,u);
        dp[u][0]^=dp[to][1];
        dp[u][1]=max(dp[u][1]^dp[to][0],dp[u][1]^dp[to][1]);
    }
    return max(dp[u][0],dp[u][1]);
}

int main()
{
    //freopen("1.txt","r",stdin);
    scanf("%d",&t);
    while (t--)
    {
        _init();
        scanf("%d",&n);
        int u,v;
        int t=0;
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&f[i]);
            t^=f[i];
        }
        for (int i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            adde(u,v,f[u]);
        }
        int q=solve(0,1);
        t^=q;
        printf("%c\n",t==q?'D':t>q?'Q':'T');
    }
    return 0;
}
