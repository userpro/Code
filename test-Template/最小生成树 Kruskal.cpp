//h1083
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int N=301,M=100000;
struct Edge {int u,v,w;} e[M];
int n,m,ans,fa[N],tot=0;

inline bool cmp(Edge a,Edge b)
  {
    return a.w<b.w;
  }
int Find(int k)
  {
    if (fa[k]==k) return k;
    return fa[k]=Find(fa[k]);
  }
void Kruskal()
  {
    sort(e+1,e+m+1,cmp);
    for (int i=1;i<=n;++i) fa[i]=i;
    for (int i=1;i<=m;++i)
      {
        int p=Find(e[i].u);
        int q=Find(e[i].v);
        if (p!=q)
          {
            fa[p]=q;
            ans=e[i].w;
            tot+=e[i].w;
          }
      }
  }
int main()
  {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;++i)
      scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    Kruskal();
    printf("%d %d\n",n-1,ans);
  }