//h1776
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=200001,H=20;
int f[N][H],d[N],a[N],n,p,k,root,x,y,max_d[N],r[N],Q[N],ans[N];
struct edge {int u,v;edge *next;} e[N],*point[N],*P=e;
inline void add_edge(int a,int b)
  {
    P->u=a;P->v=b;P->next=point[a];point[a]=P++;
  }
void bfs()
  {
    int h,t,x;f[root][0]=0;d[root]=1;
    max_d[a[root]]=d[root],r[a[root]]=root;
    for (Q[h=t=1]=root;h<=t;++h)
      for (edge *j=point[x=Q[h]];j;j=j->next)
        if (j->v!=f[x][0]) 
          {
            f[j->v][0]=x,d[j->v]=d[x]+1;
            if (d[j->v]>max_d[a[j->v]])
              max_d[a[j->v]]=d[j->v],r[a[j->v]]=j->v;
            Q[++t]=j->v;
          }
  }
inline int lca(int a,int b)
  {
    if (d[a]<d[b]) swap(a,b);
    for (int i=H-1;i>=0;--i)
      if (d[f[a][i]]>=d[b]) a=f[a][i];
    if (a==b) return a;
    for (int i=H-1;i>=0;--i)
      if (f[a][i]!=f[b][i]) a=f[a][i],b=f[b][i];
    return f[a][0];
  }
int main()
  {
    scanf("%d%d",&n,&k);
    for (int i=1;i<=n;++i)
      {
        scanf("%d%d",&a[i],&p);
        if (p) add_edge(p,i);else root=i;
      }
    bfs();
    for (int j=1;j<H;++j)
      for (int i=1;i<=n;++i)
        f[i][j]=f[f[i][j-1]][j-1];
    for (int i=1;i<=n;++i)
      if (r[a[i]]!=i)
        {
          x=r[a[i]];y=i;
          ans[a[i]]=max(ans[a[i]],d[x]+d[y]-2*d[lca(x,y)]);
        }
    for (int i=1;i<=k;++i) printf("%d\n",ans[i]);
  }
    