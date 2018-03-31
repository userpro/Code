#include<stdio.h>
#include<math.h>
int num[100010],f[100010],MAX[100010][20];
int n;
int max(int a,int b)
{
    return a>b?a:b;
}
void ST()
{
    int i,j,k;
    for(i=1;i<=n;i++)
        MAX[i][0]=f[i];
    k=log((double)(n+1))/log(2.0);
    for(j=1;j<=k;j++)
        for(i=1;i+(1<<j)-1<=n;i++)
            MAX[i][j]=max(MAX[i][j-1],MAX[i+(1<<(j-1))][j-1]);
}
int rmq_max(int l,int r)
{
    if(l>r)
        return 0;
    int k=log((double)(r-l+1))/log(2.0);
    return max(MAX[l][k],MAX[r-(1<<k)+1][k]);
}
int main()
{
    int q,i,a,b;
    while(scanf("%d",&n)&&n)
    {
        scanf("%d",&q);
        for(i=1;i<=n;i++)
        {
            scanf("%d",&num[i]);
            if(i==1)
            {
                f[i]=1;
                continue;
            }
            if(num[i]==num[i-1])
                f[i]=f[i-1]+1;
            else
                f[i]=1;
        }
        ST();
        for(i=1;i<=q;i++)
        {
            scanf("%d%d",&a,&b);
            int t=a;
            while(t<=b&&num[t]==num[t-1])
                t++;
            int cnt=rmq_max(t,b);
            int ans=max(t-a,cnt);
            printf("%d\n",ans);
        }
    }
    return 0;
}