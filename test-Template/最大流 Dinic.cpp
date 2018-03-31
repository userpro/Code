//h2039
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=1050,M=N*N*2,inf=2147483647;
struct edge {int u,v,w;edge *next,*other;} e[M],*point[N],*last[N],*P=e;
inline void add_edge(int a,int b,int c)
  {
    edge *Q=++P;++P;
    Q->u=a;Q->v=b;Q->w=c;Q->next=point[a];Q->other=P;point[a]=Q;
    P->u=b;P->v=a;P->w=0;P->next=point[b];P->other=Q;point[b]=P;
  }
int tot,n,S,T,num[N],d[N],flow=0,sum=0,x,s[N],Q[N];

void bfs()
  {
    memset(d,255,sizeof(d));
    memset(num,0,sizeof(num));
    d[T]=0;int h,t;
    for (Q[h=t=1]=T;h<=t;++h)
      for (edge *j=point[Q[h]];j;j=j->next)
        if (!j->w && d[j->v]==-1) d[Q[++t]=j->v]=d[j->u]+1;
    for (int i=1;i<=tot;++i) ++num[d[i]];
  }
int dfs(int now,int flow)
  {
    if (now==T) return flow;
    int ans=0;
    for (edge *j=last[now];j;j=j->next)
      if (j->w && d[now]==d[j->v]+1)
        {
          last[now]=j;
          int p=dfs(j->v,min(flow-ans,j->w));
          j->w-=p;j->other->w+=p;ans+=p;
          if (ans==flow) return ans;
        }
    if (d[S]>=tot) return ans;
    if (--num[d[now]]==0) d[S]=tot;
    ++num[++d[now]];last[now]=point[now];
    return ans;
  }
int main()
  {
    scanf("%d",&n);tot=n;S=++tot;T=++tot;
    for (int i=1;i<=n;++i) scanf("%d",&x),add_edge(i,T,x);
    for (int i=1;i<=n;++i)
      for (int j=1;j<=n;++j)
        scanf("%d",&x),sum+=x,s[i]+=x,add_edge(i,j,2*x);  
    for (int i=1;i<=n;++i) add_edge(S,i,s[i]);
    for (int i=1;i<=tot;++i) last[i]=point[i];
    bfs();
    while (d[S]<tot) flow+=dfs(S,inf);
    printf("%d\n",sum-flow);
  }