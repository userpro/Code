/*
将原序列转换一下, 
if(num[i]==num[i-1])
    f[i]=f[i-1]+1;
else
    f[i]++;

对于每个询问(l,r), 分为两个部分
前半部分求与l之前相同的数的个数直到t, 后半部分从t开始直接用RMQ求解最大值就行了.
最后结果为max(前半部分,后半部分).
*/
#include <cstdio>
#include <cstring>
#include <cmath>

#define MAXN 100010
#define max(a,b) (a>b?a:b)
int num[MAXN],f[MAXN],rmax[MAXN][20];
int n,q;

void RMQ(int _n)
{
    int i,j,k;
    for (i=1;i<=_n;i++)
        rmax[i][0]=f[i];
    k=log((double)(_n+1))/log(2.0);
    for (j=1;j<=k;j++)
        for (i=1;i+(1<<j)-1<=_n;i++)
            rmax[i][j]=max(rmax[i][j-1], rmax[i+(1<<(j-1))][j-1]);
}

int rmq_max(int l,int r)
{
    if (l>r)
        return 0;
    int k=log((double)(r-l+1))/log(2.0);
    return max(rmax[l][k], rmax[r-(1<<k)+1][k]);
}

int a,b;
int main()
{
    while (scanf("%d",&n)&&n)
    {
        scanf("%d",&q);
        f[0]=0;
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&num[i]);
            if (num[i]==num[i-1])
                f[i]=f[i-1]+1;
            else
                f[i]=1;
        }
        RMQ(n);
        for(int i=1;i<=q;i++)
        {
            scanf("%d%d",&a,&b);
            int t=a;
            while(t<=b&&num[t]==num[t-1]) // 左边小块
                t++;
            int cnt=rmq_max(t,b);
            int ans=max(t-a,cnt);
            printf("%d\n",ans);
        }
    }
    return 0;
}