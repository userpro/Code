// 点修改
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define PushUp(rt) sum[rt]=max(sum[rt<<1],sum[rt<<1|1])
#define MAXN 200005
int n,m;
int sum[MAXN<<2];
int num[MAXN];

void Build(int l, int r, int rt)
{
    if (l==r)
    {
        sum[rt]=num[l];
        return;
    }
    int m=(l+r)>>1;
    Build(l,m,rt<<1);
    Build(m+1,r,rt<<1|1);
    PushUp(rt);
}

void Update(int L, int C, int l, int r, int rt)
{
    if (l==r)
    {
        sum[rt]=C;
        return;
    }
    int m=(l+r)>>1;
    if (L<=m) Update(L,C,l,m,rt<<1);
    else Update(L,C,m+1,r,rt<<1|1);
    PushUp(rt);
}

int Query(int L, int R, int l, int r, int rt)
{
    if (L<=l && r<=R)
        return sum[rt];
    int m=(l+r)>>1;
    int ans=0;
    if (L<=m) ans=max(ans,Query(L,R,l,m,rt<<1));
    if (R>m) ans=max(ans,Query(L,R,m+1,r,rt<<1|1));
    return ans;
}

char op[3];
int a,b;
int main()
{
    while (scanf("%d%d",&n,&m) != EOF)
    {
        memset(sum,0,sizeof(sum));
        memset(num,0,sizeof(num));
        for (int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        Build(1,n,1);
        for (int i=1;i<=m;++i)
        {
            scanf("%s%d%d",op,&a,&b);
            if (op[0]=='U')
                Update(a,b,1,n,1);
            else if (op[0] == 'Q')
                printf("%d\n", Query(a,b,1,n,1));
        }
    }
    return 0;
}