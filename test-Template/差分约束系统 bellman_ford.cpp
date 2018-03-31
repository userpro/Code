//poj3169
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
const int N=1001,M=20001,inf=1999999999;
struct edge {int u,v,w;edge *next;} e[M],*P=e,*point[N];
inline void add_edge(int a,int b,int c)
  {
    P->u=a;P->v=b;P->w=c;P->next=point[a];point[a]=P++;
  }
int n,ml,md,a,b,c,f[N],S,T;
  
void bellman_ford()
  {
    memset(f,127,sizeof(f));
    f[S]=0;
    bool found;
    for (int i=1;i<=n;++i)
      {
        found=false;
        for (edge *j=e;j!=P;++j)
          if (f[j->u]+j->w<f[j->v])
            f[j->v]=f[j->u]+j->w,found=true;
        if (!found) break;
      }
    if (found) puts("-1");
      else if (f[T]>inf) puts("-2");
        else printf("%d\n",f[T]);
  }
int main()
  {
    read(n);read(ml);read(md);S=1;T=n;
    for (int i=1;i<=ml;++i) read(a),read(b),read(c),add_edge(a,b,c);
    for (int i=1;i<=md;++i) read(a),read(b),read(c),add_edge(b,a,-c);
    bellman_ford();
  }