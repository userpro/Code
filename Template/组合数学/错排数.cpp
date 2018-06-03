#define LL long long
#define MOD 1000000007
#define MAXN 10010
LL D[MAXN];

void preD()
{
    D[0]=1; D[1]=0;
    for (int i=2;i<=MAXN;i++)
        D[i]=((i-1)*(D[i-1]+D[i-2])+MOD)%MOD;
}

