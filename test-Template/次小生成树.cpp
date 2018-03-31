//poj 1679
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

typedef pair<int,int> Pii;
priority_queue<Pii,vector<Pii>,greater<Pii> > Q;
const int N=101,M=20001;
struct edge{int u,v,w,next;} e[M];
int k,point[N],d[N],pre[N],m,n,s[N],top,ans,f[N][N];
bool v[N];

void add_edge(int a,int b,int c)
  {
    k++;e[k].u=a;e[k].v=b;e[k].w=c;
    e[k].next=point[a];point[a]=k;
  }
void prim()
  {
    while (!Q.empty()) Q.pop();
    Q.push(Pii(0,1));
    memset(d,127,sizeof(d));
    d[1]=0;
    int now,t;
    while (!Q.empty())
      {
        t=Q.top().first; 
        now=Q.top().second;
        Q.pop();
        ans+=t;
        v[now]=true;
        for (int i=1;i<=top;++i)
          f[s[i]][now]=f[now][s[i]]=max(f[s[i]][pre[now]],t);
        s[++top]=now;
        for (int j=point[now];j;j=e[j].next)
          if (!v[e[j].v] && e[j].w<d[e[j].v])
            d[e[j].v]=e[j].w,pre[e[j].v]=now,
            Q.push(Pii(d[e[j].v],e[j].v));
        while (!Q.empty() && v[Q.top().second]) Q.pop();
      }
  }
int main()
  {
    int data;
    scanf("%d",&data);
    while (data)
      {
        --data;
        k=0;ans=0;top=0;
        memset(point,0,sizeof(point));
        memset(f,0,sizeof(f));
        memset(v,false,sizeof(v));
        scanf("%d%d",&n,&m);
        int a,b,c;
        for (int i=1;i<=m;++i)
          {
            scanf("%d%d%d",&a,&b,&c);
            add_edge(a,b,c);
            add_edge(b,a,c);
          }
        prim();
        int x=999999999;
        for (int i=1;i<=k;++i)
          if (pre[e[i].v]!=e[i].u &&
              pre[e[i].u]!=e[i].v)
              x=min(x,e[i].w-f[e[i].u][e[i].v]);
        if (x) printf("%d\n",ans);else printf("Not Unique!\n");
      }
  }