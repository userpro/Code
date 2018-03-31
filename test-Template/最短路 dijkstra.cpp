//t1031
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

const int N=2502,M=12402;
int n,m,S,T,d[N];
bool v[N];
typedef pair<int,int> Pii;
priority_queue <Pii,vector<Pii>,greater<Pii> > Q;
struct Edge {int u,v,w;Edge *next;} e[M],*P=e,*point[N];
inline void Add_Edge(int a,int b,int c)
  {
    P->u=a;P->v=b;P->w=c;P->next=point[a];point[a]=P++;
  }
  
void Dijkstra(int S)
  {
    memset(d,127,sizeof(d));
    memset(v,false,sizeof(v));
    d[S]=0;Q.push(Pii(d[S],S));
    while (!Q.empty())
      {
        int now=Q.top().second;Q.pop();
        if (v[now]) continue;v[now]=true;
        for (Edge *j=point[now];j;j=j->next)
          if (d[j->u]+j->w<d[j->v])
            d[j->v]=d[j->u]+j->w,Q.push(Pii(d[j->v],j->v));
      }
  }
int main()
  {
    scanf("%d%d%d%d",&n,&m,&S,&T);int a,b,c;
    for (int i=1;i<=m;++i)
      scanf("%d%d%d",&a,&b,&c),Add_Edge(a,b,c),Add_Edge(b,a,c);
    Dijkstra(S);
    printf("%d\n",d[T]);
  }