#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=200012,M=28;
int n=0,a[N],f[N],xx[N],yy[N],sw[N],vw[N],height[N],t,rank[N];
char ch;

bool same(int *r,int a,int b,int l)
  {
    return (r[a]==r[b] && r[a+l]==r[b+l]);
  }
void suffix(int *r,int *sa,int n,int m)
  {
    int *x=xx,*y=yy,*ws=sw,*wv=vw,*o;
    for (int i=0;i<m;++i) ws[i]=0;
    for (int i=0;i<n;++i) ++ws[x[i]=r[i]];
    for (int i=1;i<m;++i) ws[i]+=ws[i-1];
    for (int i=n-1;i>=0;--i) sa[--ws[x[i]]]=i;
    for (int j=1,p=1;p<n;j*=2,m=p)
      {
        p=0;
        for (int i=n-j;i<n;++i) y[p++]=i;
        for (int i=0;i<n;++i)
          if (sa[i]>=j) y[p++]=sa[i]-j;
        for (int i=0;i<n;++i) wv[i]=x[y[i]];
        for (int i=0;i<m;++i) ws[i]=0;
        for (int i=0;i<n;++i) ++ws[wv[i]];
        for (int i=1;i<m;++i) ws[i]+=ws[i-1];
        for (int i=n-1;i>=0;--i) sa[--ws[wv[i]]]=y[i];
        o=x,x=y,y=o,p=1,x[sa[0]]=0;
        for (int i=1;i<n;++i)
          if (same(y,sa[i-1],sa[i],j)) x[sa[i]]=p-1;else x[sa[i]]=p++;
      }
  }
void calc_height(int *r,int *sa)
  {
    int k=0,j;
    for (int i=0;i<n;++i) rank[sa[i]]=i;
    for (int i=0;i<n;height[rank[i++]]=k) 
      if (rank[i]==0) k=0;
        else for (k=max(k-1,0),j=sa[rank[i]-1];r[i+k]==r[j+k];++k);
  }
int main()
  {
    int *r=a,*sa=f;
    while (ch=getchar(),ch!='\n') r[n++]=ch-'a'+1;
    t=n;r[n++]=27;
    while (ch=getchar(),ch!='\n') r[n++]=ch-'a'+1;
    r[n++]=0;
    suffix(r,sa,n,M);
    calc_height(r,sa);
    int ans=0;
    for (int i=1;i<n;++i) 
      if (sa[i]>t && sa[i-1]<t || sa[i]<t && sa[i-1]>t)
        ans=max(ans,height[i]);
    printf("%d\n",ans);
  }