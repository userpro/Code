// 思路：这明显是排列组合问题。先把所有的情况求出来A(n,n)也就是n！减去错排的情况。具体就是定某些位置不动，其他位置进行错排。

// C(n,i)*D(n-i)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define MOD 1000000007
#define MAXN 10010
LL fac[MAXN],D[MAXN];
LL inv[MAXN];

LL qpow(LL x,LL y)
{
    LL res = 1;
    while(y){
        if(y&1) res = x * res % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}

void pre()
{
    CLR(D,0);
    D[0]=1; D[1]=0;
    for (int i=2;i<=MAXN;i++)
        D[i]=((i-1)*(D[i-1]+D[i-2])+MOD)%MOD;
    CLR(fac,0);
    fac[0]=1;
    for (int i=1;i<=MAXN;i++)
        fac[i]=(i*fac[i-1])%MOD;

    // 求逆元
    inv[MAXN-1]=qpow(fac[MAXN-1],MOD-2);
    for (int i=MAXN-2;i>=0;i--)
        inv[i]=(inv[i+1]*(i+1) % MOD);
}

LL C(int n,int m)
{
    return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}


int T,N,K;
int main()
{
    pre();
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            scanf("%d%d",&N,&K);
            LL res=1;
            for (int i=1;i<=N;i++)
                res=res*i%MOD;
            LL val=0;
            for (int i=0;i<K;i++)
                val=(val+D[N-i]*C(N,i))%MOD;
            printf("%lld\n", (res-val+MOD)%MOD);
        }
    }
    return 0;
}