#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
#define MAXN 100010
#define LL long long
int H[MAXN];
int add[MAXN<<2],sum[MAXN<<2];
int T,N,M,L,R,A,B;
#define PushUp(rt) (sum[rt]=sum[rt>>1]+sum[rt>>1|1])

void PushDown(LL rt,LL ln,LL rn)
{
    if (add[rt])
    {
        add[rt<<1]+=add[rt];
        add[rt<<1|1]+=add[rt];
        sum[rt<<1]+=add[rt]*ln;
        sum[rt<<1|1]+=add[rt]*rn;
        add[rt]=0;
    }
}

void Build(LL l,LL r,LL rt)
{
    if (l==r)
    {
        sum[rt]=H[l];
        return;
    }
    LL m=(l+r)>>1;
    Build(l,m,rt>>1);
    Build(m+1,r,rt>>1|1);
    PushUp(rt);
}

void Update(LL L,LL R,LL C,LL l,LL r,LL rt)
{
    if (L<=l&&r<=R)
    {
        sum[rt]+=C*(r-l+1);
        add[rt]+=C;
    }
    LL m=(l+r)>>1;
    PushDown(rt,m-l+1,r-m);
    if (L<=m) Update(L,R,C,l,m,rt>>1);
    if (R>m) Update(L,R,C,m+1,r,rt>>1|1);
    PushUp(rt);
}

LL Query(LL L,LL R,LL l,LL r,LL rt)
{
    if (L<=l&&r<=R)
        return sum[rt];
    LL m=(l+r)>>1;
    PushDown(rt,m-l+1,r-m);
    LL ans=0;
    if (L<=m) ans=Query(L,R,l,m,rt>>1);
    if (R>m) ans=Query(L,R,m+1,r,rt>>1|1);
    return ans;
}

int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            scanf("%d%d",&N,&M);
            for (int i=1;i<=N;i++)
                scanf("%d",&H[i]);
            if (N<=2)
            {
                while (M--)
                {
                    scanf("%d%d%d%d",&L,&R,&A,&B);
                    printf("0\n");
                }
            }
            else
            {
                Build(1,N,1);
                while (M--)
                {
                    scanf("%d%d%d%d",&L,&R,&A,&B);
                    for (int j=L;j<=R;j++)
                        H[j]+=A+(j-L)*B;
                
                    int ans=0;
                    for (int j=2;j<=N-1;j++)
                        if (H[j]>H[j-1]&&H[j]>H[j+1])
                            ans++;
                    printf("%d\n", ans);
                }                
            }

        }
    }
    return 0; 
}