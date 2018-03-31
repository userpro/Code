//t1922
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=10012,M=200012;
int n,m,q,a,b,f[N],tot=0,rea[N],low[N],tim=0,Z[N],top=0,fa[N];
bool v[N];
struct Edge {int u,v;Edge *next;} e[M],*P=e,*point[N];
inline void Add_Edge(int a,int b)
  {
    P->u=a;P->v=b;P->next=point[a];point[a]=P++;
  }
int Find(int x)
  {
    if (fa[x]==x) return x;return fa[x]=Find(fa[x]);
  }
void Dfs(int now,int p)
  {
    low[now]=rea[now]=++tim;Z[++top]=now;v[now]=true;
    for (Edge *j=point[now];j;j=j->next)
      if (j->v!=p)
        {
          if (!v[j->v]) Dfs(j->v,now);
          low[now]=min(low[now],low[j->v]);
        }
    if (rea[now]==low[now])
      for (++tot;Z[top+1]!=now;--top) f[Z[top]]=tot;
  }
int main()
  {
    scanf("%d%d%d",&n,&m,&q);
    for (int i=1;i<=m;++i) scanf("%d%d",&a,&b),Add_Edge(a,b),Add_Edge(b,a);
    for (int i=1;i<=n;++i) if (!v[i]) Dfs(i,-1);
    for (int i=1;i<=n;++i) fa[i]=i;
    for (Edge *j=e;j<P;++j) 
      if (f[j->u]!=f[j->v])
        fa[Find(j->u)]=Find(j->v);
    for (int i=1;i<=q;++i)
      {
        scanf("%d%d",&a,&b);
        if (Find(a)==Find(b)) puts("Y");else puts("N");
      }
  }