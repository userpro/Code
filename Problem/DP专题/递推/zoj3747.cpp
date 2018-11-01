/*
题意:
有G,R,P三种总人数和为N的士兵排成一排, 问至少有M个连续的G士兵且至多有K个连续的R士兵的情况有多少种

题解:
采用动态规划的递推方法, 因为至少和至多是两种情况不一样不好算, 所以我们把它转化为都求至多的问题. 也就是说先求
①至多N个连续G和且至多K个连续R的情况数. 
②至多M-1个连续G且至多K个连续R的情况数.
①减②即为符合至少M个G且至多K个R的情况. 

dp[i][0]表示第i个为G, 至多有u个连续G, 至多有v个连续R的个数  //这里的u和v根据题目已经确定好了
dp[i][1]表示第i个为R, ....
dp[i][2]表示第i个为P, ....

【 令 A => dp[i-1][0] + dp[i-1][1] + dp[i-1][2] 】

当第i个为P时
    不会对连续的R和G产生影响, dp[i][2] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2];
                        => dp[i][2] = A;

当第i个为G时
    如果 i <= u 时 无论怎么放都不会超过u个连续的G这个限制条件 
        所以 dp[i][0] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2];
        => dp[i][0] = A;

    如果 i = u+1 时, 要排除前u个都放了G的情况, 
        所以 dp[i][0] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2]-1;
        => dp[i][0] = A - 1;

    如果 i > u+1 时, 要排除从 i-1 到 i-u 位置都放了G的情况
    【 即从 i-1 开始往前能数出来u个G: {（i-1）-（i-u）+1=u }  】
        所以 dp[i][0] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2] - dp[i-u-1][1] - dp[i-u-1][2];
        => dp[i][0] = A - dp[i-u-1][1] - dp[i-u-1][2];
        //此时要减去i前面已经出现连续u个G的情况, 即从i-u到i-1这一段都是G, 那么i-1-u的位置可以是P或者R


当第i个为R时
    如果 i <= v 时 无论怎么放都不会超过v个连续的R这个限制条件 
        所以 dp[i][1] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2];
        => dp[i][1] = A;

    如果 i = v+1 时, 要排除前v个都放了R的情况, 
        所以 dp[i][1] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2] - 1;
        => dp[i][1] = A - 1;

    如果 i > v+1 时, 要排除从 i-1 到 i-v 位置都放了R的情况, 
        所以 dp[i][1] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2] - dp[i-v-1][0] - dp[i-v-1][2];
        => dp[i][1] = A - dp[i-v-1][0] - dp[i-v-1][2];
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1000010
#define MOD 1000000007
#define LL long long
LL dp[MAXN][3];
LL n,m,k,u,v;

LL solve()
{
    dp[0][0]=1;
    dp[0][1]=0;
    dp[0][2]=0;
    for (int i=1;i<=n;i++)
    {
        LL sum=(dp[i-1][0]+dp[i-1][1]+dp[i-1][2])%MOD;
        dp[i][2]=sum;
        if (i<=u)
            dp[i][0]=sum;
        else if (i==u+1)
            dp[i][0]=(sum-1)%MOD;
        else
            dp[i][0]=(sum-dp[i-u-1][1]-dp[i-u-1][2])%MOD;

        if (i<=v)
            dp[i][1]=sum;
        else if (i==v+1)
            dp[i][1]=(sum-1)%MOD;
        else
            dp[i][1]=(sum-dp[i-v-1][0]-dp[i-v-1][2])%MOD;

    }

    return (dp[n][0]+dp[n][1]+dp[n][2])%MOD;
}

int main()
{
    while (scanf("%lld%lld%lld",&n,&m,&k)!=EOF)
    {
        u=n; v=k;
        LL ans=solve();
        u=m-1; v=k;
        ans=(ans-solve())%MOD;
        printf("%lld\n", (ans+MOD)%MOD);
    }
    return 0;
}