//t1591
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

const int N=200002,M=400002;
int n,m,k,d[N],tot=0;
long long ans=0;
bool v[N];
typedef pair<int,int> Pii;
priority_queue <Pii,vector<Pii>,greater<Pii> > Q;
struct Edge {int u,v,w;Edge *next;} e[M],*P=e,*point[N];
inline void Add_Edge(int a,int b,int c)
  {
    P->u=a;P->v=b;P->w=c;P->next=point[a];point[a]=P++;
  }
void Prim(int S)
  {
    memset(v,false,sizeof(v));
    memset(d,127,sizeof(d));
    d[S]=0;Q.push(Pii(d[S],S));
    while (!Q.empty())
      {
        int now=Q.top().second;Q.pop();
        if (v[now]) continue;
        v[now]=true;++tot;ans+=d[now];
        for (Edge *j=point[now];j;j=j->next)
          if (j->w<d[j->v]) d[j->v]=j->w,Q.push(Pii(d[j->v],j->v));
      }
  }
int main()
  {
    scanf("%d%d%d",&n,&m,&k);int a,b,c;
    for (int i=1;i<=m;++i) 
      scanf("%d%d%d",&a,&b,&c),Add_Edge(a,b,c),Add_Edge(b,a,c);
    Prim(k);
    if (tot==n) printf("%I64d\n",ans);else printf("%d\n",n-tot);
  }