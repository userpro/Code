// 区间修改
#include <cstring>
#include <cstdio>

using namespace std;
#define MAXN 100010
#define PushUp(rt) sum[rt]=sum[rt<<1]+sum[rt<<1|1]
#define LL long long
int n,q;
LL sum[MAXN<<2], add[MAXN<<2];
LL num[MAXN];

void PushDown(LL rt, LL ln, LL rn)
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


void Build(LL l, LL r, LL rt)
{
    if (l==r)
    {
        sum[rt]=num[l];
        return;
    }
    LL m=(l+r)>>1;
    Build(l,m,rt<<1);
    Build(m+1,r,rt<<1|1);
    PushUp(rt);
}

void Update(LL L, LL R, LL C, LL l, LL r, LL rt)
{
    if (L<=l && r<=R)
    {
        sum[rt]+=C*(r-l+1);
        add[rt]+=C;
        return;
    }
    LL m=(l+r)>>1;
    PushDown(rt,m-l+1,r-m);
    if (L<=m) Update(L,R,C,l,m,rt<<1);
    if (R>m) Update(L,R,C,m+1,r,rt<<1|1);
    PushUp(rt);
}

LL Query(LL L, LL R, LL l, LL r, LL rt)
{
    if (L<=l&&r<=R)
        return sum[rt];
    LL m=(l+r)>>1;
    PushDown(rt,m-l+1,r-m);
    LL ans=0;
    if (L<=m) ans+= Query(L,R,l,m,rt<<1);
    if (R>m) ans+=Query(L,R,m+1,r,rt<<1|1);
    return ans;
}

char op[3];
LL a,b,c;
int main()
{
    while (scanf("%d%d",&n,&q) != EOF)
    {
        memset(sum,0,sizeof(sum));
        memset(add,0,sizeof(add));
        memset(num,0,sizeof(num));
        for (int i=1;i<=n;i++)
            scanf("%lld",&num[i]);
        Build(1,n,1);
        for (int i=1;i<=q;i++)
        {
            scanf("%s",op);
            if (op[0]=='Q')
            {
                scanf("%lld%lld",&a,&b);
                printf("%lld\n", Query(a,b,1,n,1));
            }
            else if (op[0]=='C')
            {
                scanf("%lld%lld%lld",&a,&b,&c);
                Update(a,b,c,1,n,1);
            }
        }
    }
    return 0;
}