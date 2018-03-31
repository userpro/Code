#include <cstring>
#include <cstdio>

using namespace std;
#define PushUp(rt) sum[rt]=sum[rt<<1]+sum[rt<<1|1]
#define MAXN 50005
int T,N;
int sum[MAXN<<2];
int num[MAXN];
char cmd[20];
int op1,op2;

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
        sum[rt]+=C;
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
    if (L<=m) ans+=Query(L,R,l,m,rt<<1);
    if (R>m) ans+=Query(L,R,m+1,r,rt<<1|1);
    return ans;
}

int main()
{
    scanf("%d",&T);
    for (int i=1;i<=T;i++)
    {
        memset(sum,0,sizeof(sum));
        memset(num,0,sizeof(num));
        printf("Case %d:\n", i);
        scanf("%d",&N);
        for (int j=1;j<=N;j++)
            scanf("%d",&num[j]);
        Build(1,N,1);
        while (scanf("%s", cmd) != EOF)
        {
            if (cmd[0]=='E')
                break;
            scanf("%d%d",&op1,&op2);
            if (cmd[0]=='Q')
                printf("%d\n", Query(op1,op2,1,N,1));
            else if (cmd[0]=='A')
                Update(op1, op2, 1, N, 1);
            else if (cmd[0]=='S')
                Update(op1, -op2, 1, N, 1);
        }
    }
    return 0;
}