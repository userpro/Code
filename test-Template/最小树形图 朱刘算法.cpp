#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const int N=101,M=10001,inf=2147483647;
struct edge {int u,v,w;} e[M];
int n,m,ans,id[N],pre[N],v[N],inw[N];

void zhu_liu(int root)
  {
    int s,t,idx=n;
    while (idx)
      {
        for (int i=1;i<=n;++i) inw[i]=inf,id[i]=-1,v[i]=-1;
        for (int i=1;i<=m;++i)
          {
            s=e[i].u;t=e[i].v;
            if (e[i].w>inw[t] || s==t) continue;
            pre[t]=s;
            inw[t]=e[i].w;
          }
        inw[root]=0;pre[root]=root;
        for (int i=1;i<=n;++i)
          {
            if (inw[i]==inf)
              {
                printf("impossible\n");
                return;
              }
            ans+=inw[i];
          }
        idx=0;
        for (int i=1;i<=n;++i)
          if (v[i]==-1)
            {
              t=i;
              while (v[t]==-1) v[t]=i,t=pre[t];
              if (v[t]!=i || t==root) continue;
              id[t]=++idx;
              for (s=pre[t];s!=t;s=pre[s]) id[s]=idx;
            }
        if (idx==0) continue;
        for (int i=1;i<=n;++i)
          if (id[i]==-1) id[i]=++idx;
        for (int i=1;i<=m;++i)
          {
            e[i].w-=inw[e[i].v];
            e[i].u=id[e[i].u];
            e[i].v=id[e[i].v];
          }
        n=idx;
        root=id[root];
      }
    printf("%d\n",ans);
  }
int main()
  {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;++i)
      scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    zhu_liu(1);
    return 0;
  }