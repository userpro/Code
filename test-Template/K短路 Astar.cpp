//h1598
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

const int N=1012,M=10012;
typedef pair<long long,int> Pii;
priority_queue<Pii,vector<Pii>,greater<Pii> > Q;
int n,m,x[M],y[M],z[M],S,T,k;
long long d[N];
struct Edge {int u,v,w;Edge *next;} e[M],*P,*point[N];
inline void Add_Edge(int a,int b,int c)
  {
    P->u=a;P->v=b;P->w=c;P->next=point[a];point[a]=P++;
  }
void Dijkstra(int S)
  {
    memset(d,127,sizeof(d));
    d[S]=0;Q.push(Pii(0,S));
    while (!Q.empty())
      {
        int now=Q.top().second;Q.pop();
        for (Edge *j=point[now];j;j=j->next)
          if (d[j->u]+j->w<d[j->v])
            d[j->v]=d[j->u]+j->w,Q.push(Pii(d[j->v],j->v));
      }
  }
void Astar(int S)
  {
    Q.push(Pii(d[S],S));
    while (!Q.empty())
      {
        int now=Q.top().second;
        long long g=Q.top().first-d[now];
        Q.pop();
        if (now==T) 
          {
            printf("%lld\n",g);
            if (!(--k)) return;
            continue;
          }
        for (Edge *j=point[now];j;j=j->next)
          Q.push(Pii(g+j->w+d[j->v],j->v));
      }
  }
int main()
  {
    scanf("%d%d%d",&n,&m,&k);S=n;T=1;
    for (int i=1;i<=m;++i) scanf("%d%d%d",&x[i],&y[i],&z[i]);
    P=e;for (int i=1;i<=m;++i) Add_Edge(y[i],x[i],z[i]);
    Dijkstra(T);
    memset(point,0,sizeof(point));
    P=e;for (int i=1;i<=m;++i) Add_Edge(x[i],y[i],z[i]);
    Astar(S);
    while (k--) puts("-1");
  }