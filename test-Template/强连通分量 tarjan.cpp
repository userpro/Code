//poj3678
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

inline void read(int &x) 
  {
    char ch; int s=1;x=0;
    while (ch=getchar(),(ch<'0' || ch>'9') && (ch!='-'));
    if (ch=='-') s=-1; else x =ch-'0';
    while (ch=getchar(),ch>='0' && ch<='9') x*=10,x+=ch-'0';
    x*=s;
  }
  
const int N=2002,M=4000002;
struct edge {int u,v;edge *next;} e[M],*P=e,*point[N];
inline void add_edge(int a,int b)
  {
    P->u=a;P->v=b;P->next=point[a];point[a]=P++;
  }
int n,m,a,b,c,v[N],rea[N],low[N],Z[N],f[N],top=0,tot=0,tim=0;
char ch;

void dfs(int now)
  {
    rea[now]=low[now]=++tim;
    v[now]=1;Z[++top]=now;
    for (edge *j=point[now];j;j=j->next)
      {
        if (!v[j->v]) dfs(j->v);
        if (v[j->v]<2) low[now]=min(low[now],low[j->v]);
      }
    if (rea[now]==low[now])
      {
        ++tot;
        while (Z[top+1]!=now) v[Z[top]]=2,f[Z[top--]]=tot;
      }
  }
int main()
  {
    read(n);read(m);
    for (int i=1;i<=m;++i)
      {
        read(a);read(b);read(c);++a;++b;
        ch=getchar();
        if (ch=='A') 
          {
            if (c) add_edge(a,a+n),add_edge(b,b+n),add_edge(a+n,b+n),add_edge(b+n,a+n);
              else add_edge(a+n,b),add_edge(b+n,a);
          }
        if (ch=='O')
          {
            if (c) add_edge(a,b+n),add_edge(b,a+n);
              else add_edge(a,b),add_edge(b,a),add_edge(a+n,a),add_edge(b+n,b);
          }
        if (ch=='X')
          {
            if (c) add_edge(a,b+n),add_edge(b,a+n),add_edge(a+n,b),add_edge(b+n,a);
              else add_edge(a,b),add_edge(b,a),add_edge(a+n,b+n),add_edge(b+n,a+n);
          }
      }
    for (int i=1;i<=2*n;++i)
      if (!v[i]) dfs(i);
    for (int i=1;i<=n;++i) 
      if (f[i]==f[i+n]) {puts("NO");return 0;}
    puts("YES");
  }