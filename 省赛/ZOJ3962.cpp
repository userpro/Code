// 数位DP
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define LL long long
int a[20];
int num[]={6,2,5,5,4,5,6,3,7,6,6,5,4,5,5,4};
LL dp[10][100];
LL T,l,r;

LL dfs(int pos,int sum,bool limit)
{
    if (pos==-1) return sum;
    if (!limit&&dp[pos][sum]!=-1) return dp[pos][sum];
    int up=limit?a[pos]:15;
    LL ret=0;
    for (int i=0;i<=up;i++)
        ret+=dfs(pos-1,sum+num[i],limit && i==up);
    if (!limit) dp[pos][sum]=ret;
    return ret;
}

LL solve(LL x)
{
    for (int i=0;i<8;i++)
    {
        a[i]=x%16;
        x/=16;
    }
    return dfs(7,0,true);
}

int main()
{
    memset(dp,-1,sizeof(dp));
    scanf("%lld",&T);
    while (T--)
    {
        scanf("%lld%llx",&l,&r);
        if (l+r-1<=0xffffffff)
            printf("%lld\n", solve(r+l-1)-solve(r-1));
        else
            printf("%lld\n", solve(0xffffffff)-(solve(r-1)-solve(r+l-1)));
    }
    return 0;
}