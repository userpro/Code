//t1730
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

#define I this
const int N=50001,M=50001,K=1000000,inf=2147483647;
int n,m,nr,ans,tot=0,num=0,ld,rd,res;
int opt[M],k[M],ql[M],qr[M],pos[M],x[M+N],past[M+N],a[N];

bool found;


inline void read(int &x) 
  {
    char ch; int s=1;x=0;
    while (ch=getchar(),(ch<'0' || ch>'9') && (ch!='-'));
    if (ch=='-') s=-1; else x =ch-'0';
    while (ch=getchar(),ch>='0' && ch<='9') x*=10,x+=ch-'0';
    x*=s;
  }
inline int ls(int k)
  {
    int l=1,r=num,mid;
    while (l<=r)
      {
        mid=(l+r)>>1;
        if (k==past[mid]) return mid;
        if (k<past[mid]) r=mid-1;else l=mid+1;
      }
  }
struct Snode
  {
    Snode *l,*r,*p;
    int d,size;
    inline void update() {size=l->size+r->size+1;}
    inline bool is_l() {return I==p->l;}
    inline void set_l(Snode *x) {l=x;x->p=I;}
    inline void set_r(Snode *x) {r=x;x->p=I;}
    inline void left()
      {
        Snode *fa=p;
        if (fa->is_l()) fa->p->set_l(I);
          else fa->p->set_r(I);
        fa->set_r(l);
        set_l(fa);
        fa->update();
      }
    inline void right()
      {
        Snode *fa=p;
        if (fa->is_l()) fa->p->set_l(I);
          else fa->p->set_r(I);
        fa->set_l(r);
        set_r(fa);
        fa->update();
      }
    inline int rank(int x)
      {
        if (d==-1) return 1;
        if (d==x) found=true;
        if (d>=x) return l->rank(x);
          else return r->rank(x)+l->size+1;
      }
    inline void pred(int x)
      {
        if (d==-1) return;
        if (d<x) res=max(res,d),r->pred(x);
          else l->pred(x);
      }
    inline void succ(int x)
      {
        if (d==-1) return;
        if (d>x) res=min(res,d),l->succ(x);
          else r->succ(x);
      }
  } T[K],*P=T,*nil=T;
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
    root=++P;
    root->l=root->r=nil;
    root->size=1;root->d=x;
    if (x<fa->d) fa->set_l(root);
      else fa->set_r(root);
    splay(past,root,nil);
  }
inline void del(Snode *&root,int t)
  {
    Snode *x=root;
    while (x->d!=t)
      if (x->d<t) x=x->r;else x=x->l;
    splay(root,x,nil);
    if (root->l==nil) 
      {
        root=root->r;root->p=nil;
        return;
      }
    Snode *past=nil;
    for (Snode *t=root->l;t!=nil;t=t->r) past=t;
    splay(root,past,root);
    past->p=nil;past->set_r(root->r);
    root=past;
    root->update();
  }


  
  
int lx[N*5],rx[N*5],root[N*5];
struct Xnode
  {
    Xnode *l,*r;
    Snode *root;
    int lx,rx,mid;
    inline void rank(int x)
      {
        if (ld<=lx && rd>=rx) 
          {
            res+=root->rank(x)-1;
            return;
          }
        if (ld<=mid) l->rank(x);
        if (rd>mid) r->rank(x);
      }
    inline void pred(int x)
      {
        if (ld<=lx && rd>=rx)
          {
            root->pred(x);
            return;
          }
        if (ld<=mid) l->pred(x);
        if (rd>mid) r->pred(x);
      }
    inline void succ(int x)
      { 
        if (ld<=lx && rd>=rx) 
          {
            root->succ(x);
            return;
          }
        if (ld<=mid) l->succ(x);
        if (rd>mid) r->succ(x);
      }
    inline void change(int pos,int past,int now)
      {
        del(root,past);
        insert(root,now);
        if (lx==rx) return;
        if (pos<=mid) l->change(pos,past,now);
          else r->change(pos,past,now);
      }
  } X[N*5],*Q=X,*Xroot;
inline void build(Xnode *&node,int left,int right)
  {
    node=++Q;
    node->lx=left;node->rx=right;
    node->mid=(left+right)>>1;
    node->root=nil;
    for (int i=left;i<=right;++i)
      insert(node->root,a[i]);
    if (left<right)
      {
        build(node->l,left,node->mid);
        build(node->r,node->mid+1,right);
      }
  }

int find(int k)
  {
    int ans=0,last=-1;
    Snode *now=Xroot->root;
    while (now!=nil)
      {
        found=false;
        if (now->d!=last) res=1,Xroot->rank(now->d);
        last=now->d;
        if (res<=k)
          {
            if (found) ans=now->d;
            now=now->r;
          }
          else now=now->l;
      }
    return past[ans];
  }

int main()
  {
    nil->d=-1;
    read(n);read(m);nr=n;
    for (int i=1;i<=n;++i) read(a[i]),x[i]=a[i];
    for (int i=1;i<=m;++i)
      {
        read(opt[i]);
        if (opt[i]==3) read(pos[i]);
          else read(ql[i]),read(qr[i]);
        read(k[i]);
        if (opt[i]!=2) x[++nr]=k[i];
      }
    sort(x+1,x+nr+1);x[0]=-inf;
    for (int i=1;i<=nr;++i)
      {
        if (x[i]!=x[i-1]) ++num;
        past[num]=x[i];
      }
    for (int i=1;i<=n;++i) a[i]=ls(a[i]);
    build(Xroot,1,n);
    for (int i=1;i<=m;++i)
      if (opt[i]!=2) k[i]=ls(k[i]);
    for (int i=1;i<=m;++i)
      {
        ld=ql[i];rd=qr[i];
        if (opt[i]==1) res=1,Xroot->rank(k[i]),printf("%d\n",res);
        if (opt[i]==2) printf("%d\n",find(k[i]));
        if (opt[i]==3) Xroot->change(pos[i],a[pos[i]],k[i]),a[pos[i]]=k[i];
        if (opt[i]==4) 
          {
            res=-inf;Xroot->pred(k[i]);
            printf("%d\n",past[res]);
          }
        if (opt[i]==5)
          {
            res=inf;Xroot->succ(k[i]);
            printf("%d\n",past[res]);
          }
      }
  }