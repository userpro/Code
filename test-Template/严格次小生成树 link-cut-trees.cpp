#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

inline void read(int &x) 
  {
    char ch; int s=1;x=0;
    while (ch=getchar(),(ch<'0' || ch>'9') && (ch!='-'));
    if (ch=='-') s=-1; else x =ch-'0';
    while (ch=getchar(),ch>='0' && ch<='9') x*=10,x+=ch-'0';
    x*=s;
  }
const int N=100012,M=300012;const long long inf=999999999999999;
struct bian {int x,y,z;} b[M];
inline bool operator < (bian a,bian b)
  {
    return a.z<b.z;
  }
struct edge {int u,v,w;edge *next;} e[N*2],*R=e,*point[N];
inline void add_edge(int a,int b,int c)
  {
    R->u=a;R->v=b;R->w=c;R->next=point[a];point[a]=R++;
  }
int n,m,fa[N],Q[N];
bool can[M];
long long sum=0,ans=inf;
struct Snode 
  {
    Snode *l,*r,*p;
    bool flag;
    long long max1,max2,d;
    inline void update()
      {
        max1=max(d,max(l->max1,r->max1));
        max2=-inf;
        if (d<max1) max2=max(max2,d);
        if (l->max1<max1) max2=max(max2,l->max1);
        if (r->max1<max1) max2=max(max2,r->max1);
        max2=max(max2,max(l->max2,r->max2));
      }
    inline bool is_l() {return this==p->l;}
    inline void set_l(Snode *x) {x->p=this;l=x;}
    inline void set_r(Snode *x) {x->p=this;r=x;}
    inline void left()
      {
        Snode *fa=p;p=fa->p;
        if (fa->flag) flag=true,fa->flag=false;
          else if (fa->is_l()) fa->p->set_l(this);else fa->p->set_r(this);
        fa->set_r(l);set_l(fa);fa->update();
      }
    inline void right()
      {
        Snode *fa=p;p=fa->p;
        if (fa->flag) flag=true,fa->flag=false;
          else if (fa->is_l()) fa->p->set_l(this);else fa->p->set_r(this);
        fa->set_l(r);set_r(fa);fa->update();
      }
  } T[N],*P=T,*nil=T,*pos[N];
inline void splay(Snode *x)
  {
    while (!x->flag)
      {
        if (x->p->flag)
          {
            if (x->is_l()) x->right();else x->left();
            break;
          }
        if (x->p->is_l())
          if (x->is_l()) x->p->right(),x->right();
            else x->left(),x->right();
        else
          if (x->is_l()) x->right(),x->left();
            else x->p->left(),x->left();
      }
    x->update();
  }
inline void newnode(Snode *&node,int x,Snode *fa,long long d)
  {
    node=++P;node->l=node->r=nil;node->flag=true;node->p=fa;
    node->d=d;
    node->update();
  }
void bfs()
  {
    int h,t;
    nil->l=nil;nil->r=nil;nil->p=nil;nil->flag=false;
    nil->max1=nil->max2=nil->d=-inf;
    newnode(pos[1],1,nil,-inf);
    for (Q[h=t=1]=1;h<=t;++h)
      for (edge *j=point[Q[h]];j;j=j->next)
        if (pos[j->v]==NULL) newnode(pos[j->v],j->v,pos[Q[h]],j->w),Q[++t]=j->v;
  }
void query(Snode *x,Snode *y,int z)
  {
    long long max1,max2;
    Snode *i=nil;
    while (x!=nil)
      { 
        splay(x);
        x->r->flag=true;i->flag=false;x->r=i;x->update();i=x;x=x->p;
      }
    i=nil;
    while (y!=nil)
      { 
        splay(y);
        if (y->p==nil) 
          {
            max1=max(i->max1,y->r->max1);
            max2=max(i->max2,y->r->max2);
            if (i->max1<max1) max2=max(max2,i->max1);
            if (y->r->max1<max1) max2=max(max2,y->r->max1);
            if (z>max1) ans=min(ans,sum+z-max1);
              else ans=min(ans,sum+z-max2);
          }
        y->r->flag=true;i->flag=false;y->r=i;y->update();i=y;y=y->p;
      }
  }
int find(int k)
  {
    if (fa[k]==k) return k;
    return fa[k]=find(fa[k]);
  }
int main()
  {
    read(n);read(m);
    for (int i=1;i<=m;++i) read(b[i].x),read(b[i].y),read(b[i].z);
    sort(b+1,b+m+1);
    for (int i=1;i<=n;++i) fa[i]=i;
    for (int i=1;i<=m;++i) 
      {
        int p=find(b[i].x),q=find(b[i].y);
        if (p!=q) 
          {
            fa[p]=q;sum+=b[i].z;can[i]=true;
            add_edge(b[i].x,b[i].y,b[i].z);
            add_edge(b[i].y,b[i].x,b[i].z);
          }
      }
    bfs();
    for (int i=1;i<=m;++i)
      if (!can[i]) query(pos[b[i].x],pos[b[i].y],b[i].z);
    printf("%lld\n",ans);
  }