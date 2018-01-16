#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define maxn 1010
struct Node
{
    int sh,eh,eff;
}node[maxn];
int n,m,r;
int dp[maxn];

bool cmp(Node n1,Node n2)
{
    return n1.eh<n2.eh;
}

int main()
{
    while (scanf("%d%d%d",&n,&m,&r)==3)
    {
        memset(dp,0,sizeof(dp));
        for (int i = 0; i < m; ++i)
            scanf("%d%d%d",&node[i].sh,&node[i].eh,&node[i].eff);
        sort(node,node+m,cmp);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (node[j].eh<=node[i].sh-r || node[j].sh>=node[i].eh+r)
                    dp[i]=max(dp[i],dp[j]+node[i].eff);
            }
        }

        int ans=0;
        for (int i = 0; i < m; ++i)
        {
            if (ans<dp[i])
                ans=dp[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}