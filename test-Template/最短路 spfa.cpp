//t1031
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=2502,M=12402;
int n,m,S,T,d[N],Q[1000000];
bool v[N];
struct Edge {int u,v,w;Edge *next;} e[M],*P=e,*point[N];
inline void Add_Edge(int a,int b,int c)
  {
    P->u=a;P->v=b;P->w=c;P->next=point[a];point[a]=P++;
  }
  
void SPFA(int S)
  {
    memset(d,127,sizeof(d));
    memset(v,false,sizeof(v));
    d[S]=0;v[S]=true;int h,t;
    for (Q[h=t=0]=S;v[Q[h]]=false,h<=t;++h)
      for (Edge *j=point[Q[h]];j;j=j->next)
        if (d[j->u]+j->w<d[j->v])
          {
            d[j->v]=d[j->u]+j->w;
            if (!v[j->v]) Q[++t]=j->v,v[j->v]=true;
          }
  }
int main()
  {
    scanf("%d%d%d%d",&n,&m,&S,&T);int a,b,c;
    for (int i=1;i<=m;++i)
      scanf("%d%d%d",&a,&b,&c),Add_Edge(a,b,c),Add_Edge(b,a,c);
    SPFA(S);
    printf("%d\n",d[T]);
  }