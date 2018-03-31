//poj1741
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

const int N=10012,M=N*2,K=10010000,inf=9999999;
struct edge {int u,v,w;edge *next;} e[M],*P=e,*point[N];
inline void add_edge(int a,int b,int c)
  {
    ++P;P->u=a;P->v=b;P->w=c;P->next=point[a];point[a]=P;
  }
int n,tot,fa[N],size[N],maxsize[N],f[N],Q[N],ans,k;
bool v[N];

struct Snode
  {
    Snode *l,*r,*p;
    int d,size;
    inline void update() {size=l->size+r->size+1;}
    inline bool is_l() {return this==p->l;}
    inline void set_l(Snode *x) {l=x;x->p=this;}
    inline void set_r(Snode *x) {r=x;x->p=this;}
    inline void left()
      {
        Snode *fa=p;
        if (fa->is_l()) fa->p->set_l(this);
          else fa->p->set_r(this);
        fa->set_r(l);
        set_l(fa);
        fa->update();
      }
    inline void right()
      {
        Snode *fa=p;
        if (fa->is_l()) fa->p->set_l(this);
          else fa->p->set_r(this);
        fa->set_l(r);
        set_r(fa);
        fa->update();
      }
    inline int count(int x)
      {
        if (d==inf) return 0;
        if (d>x) return l->count(x);
          else return r->count(x)+l->size+1;
      }
  } T[N],*R=T,*nil=T,*root;
inline void splay(Snode *&root,Snode *x,Snode *y)
  {
    while (x->p!=y)
      {
        if (x->p->p==y)
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
    if (y==nil) root=x;
  }
inline void insert(Snode *&root,int x)
  {
    Snode *fa=nil,*past=root;
    while (root!=nil)
      {
        fa=root;
        ++root->size;
        if (x<root->d) root=root->l;
          else root=root->r;
      }
    root=++R;
    root->l=root->r=nil;
    root->size=1;root->d=x;
    if (x<fa->d) fa->set_l(root);
      else fa->set_r(root);
    splay(past,root,nil);
  }

  
void clear()
  {
    for (int i=1;i<=n;++i) point[i]=NULL;
    memset(v,false,sizeof(v));
    P=e;ans=0;nil->d=inf;
  }
int get(int x)
  {
    int h,t;
    for (fa[x]=-1,Q[h=t=1]=x;x=Q[h],h<=t;++h)
      for (edge *j=point[x];j;j=j->next)
        if (!v[j->v] && fa[x]!=j->v) fa[j->v]=x,Q[++t]=j->v;
    tot=t;
    for (int i=tot;i;--i)
      {
        x=Q[i];size[x]=1;maxsize[x]=0;
        for (edge *j=point[x];j;j=j->next)
          if (!v[j->v] && fa[x]!=j->v) 
            size[x]+=size[j->v],maxsize[x]=max(maxsize[x],size[j->v]);
        maxsize[x]=max(maxsize[x],tot-size[x]);
      }
    int w=Q[1];
    for (int i=2;i<=t;++i)
      if (maxsize[Q[i]]<maxsize[w]) w=Q[i];
    return w;
  }
void dct(int x)
  {
    x=get(x);
    v[x]=true;fa[x]=-1;root=nil;R=nil;f[x]=0;insert(root,0);
    for (edge *j=point[x];j;j=j->next)
      if (!v[j->v])
        {
          fa[j->v]=x;f[j->v]=j->w;
          int h,t,x;
          for (Q[h=t=1]=j->v;x=Q[h],h<=t;++h)
            {
              ans+=root->count(k-f[x]);
              for (edge *j=point[x];j;j=j->next)
                if (!v[j->v] && fa[x]!=j->v) 
                  f[j->v]=f[x]+j->w,fa[j->v]=x,Q[++t]=j->v;
            }
          for (int i=1;i<=t;++i) insert(root,f[Q[i]]);
        }
    for (edge *j=point[x];j;j=j->next)
      if (!v[j->v]) dct(j->v);
  }
int main()
  {
    while (read(n),n)
      {
        read(k);int a,b,c;
        clear();
        for (int i=1;i<n;++i)
          read(a),read(b),read(c),add_edge(a,b,c),add_edge(b,a,c);
        dct(1);
        printf("%d\n",ans);
      }
  }