// 数位DP
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define LL long long
int a[10];
LL dp[10][2];
int l,r;

LL dfs(int pos,int pre,int state,bool limit)
{
    if (pos==-1) return 1;
    if (!limit && dp[pos][state]!=-1) return dp[pos][state];
    int up=limit?a[pos]:9;
    int tmp=0;
    for (int i=0;i<=up;i++)
    {
        if (pre==6 && i==2) continue;
        if (i==4) continue;
        tmp+=dfs(pos-1,i,i==6,limit&&i==a[pos]);
    }
    if (!limit) dp[pos][state]=tmp;
    return tmp;
}

LL solve(int x)
{
    int cnt=0;
    while (x>0)
    {
        a[cnt++]=x%10;
        x/=10;
    }
    return dfs(cnt-1,-1,0,true);
}

int main()
{
    while (scanf("%d%d",&l,&r)!=EOF && (l||r))
    {
        memset(dp,-1,sizeof(dp));
        printf("%lld\n", solve(r)-solve(l-1));
    }
    return 0;
}