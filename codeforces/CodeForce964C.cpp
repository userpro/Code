// https://blog.csdn.net/zhao5502169/article/details/79997719
// 因为这个序列是满足k循环的, 所以我们应该主要考虑a, b的变化, 如果把这个求和公式展开后我们可以发现如果我们按k个隔开, 发现他们是符合等比序列的, 公比q = (b/a)^k . 所以我们可以利用等比公式来求前N项和.  
// 而a1就是前k项的和. 中间求一下逆元就行了. 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;
#define INF ((LL)1E18)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define MAXN 100010
#define MOD ((LL)(1E9+9))

LL n,a,b,k;
char buf[MAXN];

LL qpow(LL n,LL m)
{
    LL res=1;
    while (m>0)
    {
        if (m&1)
            res=res*n%MOD;
        n=n*n%MOD;
        m>>=1;
    }
    return res%MOD;
}

LL solve()
{
    LL a1=0;
    for (int i=0;i<k;i++)
    {
        LL si=buf[i]=='+'?1:-1;
        a1=(a1 + si * qpow(a,n-i) * qpow(b,i) % MOD+MOD)%MOD;
    }
    LL q=b * qpow(a,MOD-2) % MOD;
    q=qpow(q,k);
    LL num=(n+1)/k;
    LL sum=0;
    if (q==1)
        sum=a1*num%MOD;
    else
        sum=(a1*(qpow(q,num)-1)%MOD*qpow(q-1,MOD-2)+MOD)%MOD;
    return sum;
}

int main()
{
    while (scanf("%lld%lld%lld%lld",&n,&a,&b,&k)!=EOF)
    {
        scanf("%s",buf);
        printf("%lld\n", solve());
    }
    return 0;
}