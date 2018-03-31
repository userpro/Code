#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

const int N=10001,M=500001;
typedef pair<int,int> Pii;
priority_queue <Pii,vector<Pii>,greater<Pii> > Q;
stack<int> Z;
struct edge {int u,v,next,w;} e[M*2];
int n,m,t,tim=0,tot=0,k=0,l=0,f[N],d[N],v[N],point[N],low[N],rea[N];
long long ans;
bool can[N];

inline void add_edge(int a,int b,int c)
  {
    ++k;e[k].u=a;e[k].v=b;e[k].w=c;
    e[k].next=point[a];point[a]=k;
  }
void dfs(int now)
  {
    rea[now]=low[now]=++tim;
    v[now]=1;Z.push(now);
    for (int j=point[now];j;j=e[j].next)
      {
        if (!v[e[j].v]) dfs(e[j].v);
        if (v[e[j].v]<2) low[now]=min(low[now],low[e[j].v]);
      }
    if (low[now]==rea[now])
      {
        int last=-1;++tot;
        while (last!=now)
          {
            last=Z.top();Z.pop();
            v[last]=2;
            f[last]=tot;
          }
      }
  }   
void prim()
  {
    int now;
    memset(d,127,sizeof(d));
    d[1]=0;Q.push(Pii(0,1));
    while (!Q.empty())
      {
        for (now=Q.top().second;can[now];Q.pop(),now=Q.top().second)
          if (Q.empty()) return;
        can[now]=true;--tot;
        ans+=d[now];
        for (int j=point[now];j;j=e[j].next)
          if (e[j].w<d[e[j].v])
            {
              d[e[j].v]=e[j].w;
              Q.push(Pii(d[e[j].v],e[j].v));
            }
      }
  }
inline void read(int &x) 
  {
    char ch; int s=1;x=0;
    while (ch=getchar(),(ch<'0' || ch>'9') && (ch!='-'));
    if (ch=='-') s=-1; else x =ch-'0';
    while (ch=getchar(),ch>='0' && ch<='9') x*=10,x+=ch-'0';
    x*=s;
  }
int main()
  {
    read(n);read(m);read(t);
    int a,b,c;
    for (int i=1;i<=m;++i)
      {
        read(a);read(b);
        add_edge(a,b,0);
      }
    for (int i=1;i<=n;++i) 
      if (!v[i]) dfs(i);
    memset(point,0,sizeof(point));
    k=0;
    for (int i=1;i<=t;++i)
      {
        read(a);read(b);read(c);
        a=f[a];b=f[b];
        if (a!=b) add_edge(a,b,c),add_edge(b,a,c);
      }
    prim();
    if (tot) puts("Impossible");
      else printf("%I64d\n",ans);
  }