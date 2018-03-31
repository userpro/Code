//h1585
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=6100,M=100000,INF=999999999;
struct Edge {int u,v,w;Edge *next,*other;} e[M],*P=e,*point[N],*last[N];
inline void Add_Edge(int a,int b,int c)
  {
    Edge *Q=++P;++P;
    Q->u=a;Q->v=b;Q->w=c;Q->next=point[a];point[a]=last[a]=Q;Q->other=P;
    P->u=b;P->v=a;P->w=0;P->next=point[b];point[b]=last[b]=P;P->other=Q;
  }
int n,m,tot,S,T,flow,k,a,b,d[N],num[N];
  
int Dfs(int now,int flow)
  {
    if (now==T) return flow;
    int ans=0;
    for (Edge *j=last[now];j;j=j->next)
      if (j->w && d[j->u]==d[j->v]+1)
        {
          last[now]=j;
          int p=Dfs(j->v,min(flow-ans,j->w));
          j->w-=p;j->other->w+=p;ans+=p;
          if (ans==flow) return flow;
        }
    if (d[S]>=tot) return ans;
    if (--num[d[now]]==0) d[S]=tot;
    ++num[++d[now]];last[now]=point[now];
    return ans;
  }
void Get()
  {
    flow=0;
    memset(num,0,sizeof(num));
    memset(d,0,sizeof(d));
    num[0]=tot;
    while (d[S]<tot) flow+=Dfs(S,INF);
    printf("%d\n",flow);
  }
int main()
  {
    scanf("%d%d%d",&n,&m,&k);tot=n*2;S=++tot;T=++tot;
    Add_Edge(S,n+1,INF);for (int i=1;i<=n;++i) Add_Edge(i,i+n,1);
    for (int i=1,a,b;i<=m;++i)
      scanf("%d%d",&a,&b),Add_Edge(a+n,b,INF),Add_Edge(b+n,a,INF);
    for (int i=1,x;i<=k;++i)
      scanf("%d",&x),Add_Edge(x,T,INF);
    Get();
  }