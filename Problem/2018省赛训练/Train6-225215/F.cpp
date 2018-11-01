// 后缀数组
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 200010

int sa[MAXN];
int t1[MAXN],t2[MAXN],c[MAXN];
int rank1[MAXN],height[MAXN];
void build_sa(int s[],int n,int m)
{
    int i,j,p,*x=t1,*y=t2;
    for(int i=0; i<m; i++) c[i]=0;
    for(int i=0; i<n; i++) c[x[i]=s[i]]++;
    for(int i=0; i<m; i++) c[i]+=c[i-1];
    for(int i=n-1; i>=0; i--) sa[--c[x[i]]]=i;
    for(j=1; j<=n; j<<=1)
    {
        p=0;
        for(i=n-j; i<n; i++) y[p++]=i;
        for(i=0; i<n; i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0; i<m; i++) c[i]=0;
        for(i=0; i<n; i++) c[x[y[i]]]++;
        for(i=0; i<m; i++) c[i]+=c[i-1];
        for(i=n-1; i>=0; i--) sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;
        x[sa[0]]=0;
        for(i=1; i<n; i++)
            x[sa[i]]=(y[sa[i-1]]==y[sa[i]])&&(y[sa[i-1]+j]==y[sa[i]+j])?p-1:p++;
        if(p>=n) break;
        m=p;
    }
}
void getheight(int s[],int n)
{
    int i,j,k=0;
    for(i=0;i<=n;i++) rank1[sa[i]]=i;
    for(i=0;i<n;i++)
    {
        if(k) k--;
        j=sa[rank1[i]-1];
        while(s[i+k]==s[j+k]) k++;
        height[rank1[i]]=k;
    }
    return;
}
int s[MAXN];

int T,n,m;
char ans[MAXN];
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        for (int Case=1;Case<=T;Case++)
        {
            scanf("%d%d",&n,&m);
            int a,b,k=0;
            for (int i=0;i<n;i++)
            {
                scanf("%d",&a);
                s[k++]=a+'0';
            }
            s[k++]=0;
            for (int i=0;i<m;i++)
            {
                scanf("%d",&b);
                s[k++]=b+'0';
            }
            s[k]=0;

            build_sa(s,k+1,127);
            getheight(s,k);

            int i,j,cnt;
            i=cnt=0; j=n+1;
            while (i<n&&j<n+1+m)
            {
                if (s[i]>s[j])
                    ans[cnt++]=s[i++];
                else if (s[i]<s[j])
                    ans[cnt++]=s[j++];
                else if (rank1[i]<rank1[j])
                    ans[cnt++]=s[j++];
                else
                    ans[cnt++]=s[i++];
            }
            while (i<n) ans[cnt++]=s[i++];
            while (j<n+m+1) ans[cnt++]=s[j++];
            ans[n+m]=0;
            printf("Case %d: %s\n", Case, ans);
        }
    }
    return 0;
}