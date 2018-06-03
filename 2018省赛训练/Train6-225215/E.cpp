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

#define MAXN 10010
#define MOD 1000000007
int T,N,K;
int num[MAXN][6];

void pre()
{
    LL tmp=1;
    for (int i=1;i<MAXN;i++)
        num[i][0]=1;
    for (int k=1;k<=5;k++)
    {
        for (int j=1;j<MAXN;j++)
        {
            num[j][k]=0;
            tmp=1;
            for (int i=1;i<=k;i++)
                tmp=(tmp*j)%MOD;
            num[j][k]=(num[j][k]+tmp)%MOD;
        }
    }
}

int main()
{
    pre();
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            scanf("%d%d",&N,&K);
            LL ans=0;
            for (int i=1;i<=N;i++)
                ans=(ans+num[i][K])%MOD;
            printf("%lld\n", ans);
        }
    }
    return 0;
}