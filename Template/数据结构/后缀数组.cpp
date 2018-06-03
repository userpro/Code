#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 200010
int sa[MAXN];
int t1[MAXN],t2[MAXN],c[MAXN];
int rank[MAXN],height[MAXN];
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
    for(i=0;i<=n;i++) rank[sa[i]]=i;
    for(i=0;i<n;i++)
    {
        if(k) k--;
        j=sa[rank[i]-1];
        while(s[i+k]==s[j+k]) k++;
        height[rank[i]]=k;
    }
    return;
}
int s[MAXN];

char s1[MAXN];
int main(int argc, char const *argv[])
{
    scanf("%s",s1);
    int len=strlen(s1);
    for (int i=0;i<len;i++)
        s[i]=s1[i];
    
    int k=len;
    build_sa(s,k+1,127); // k+1 !!!
    getheight(s,k);
    
    return 0;
}