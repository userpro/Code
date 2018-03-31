//h1861
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=80012;
int n,m,x,y,z;
char opt,ch;
struct Snode 
  {
    Snode *lch,*rch,*p;
    int id,size;
    inline void update(){size=lch->size+rch->size+1;}
    inline bool is_l() {return this==p->lch;}
    inline void set_l(Snode *x) {lch=x;x->p=this;}
    inline void set_r(Snode *x) {rch=x;x->p=this;}
    inline void left()
      {
        Snode *fa=p;
        if (fa->is_l()) fa->p->set_l(this);
          else fa->p->set_r(this);
        fa->set_r(lch);set_l(fa);fa->update();
      }
    inline void right()
      {
        Snode *fa=p;
        if (fa->is_l()) fa->p->set_l(this);
          else fa->p->set_r(this);
        fa->set_l(rch);set_r(fa);fa->update();
      }
    inline Snode *rank(int k)
      {
        if (lch->size+1==k) return this;
        if (lch->size+1<k) return rch->rank(k-lch->size-1);
          else return lch->rank(k);
      }
  } T[2*N],*P=T,*nil=T,*root,*pos[N],*ld,*rd;
inline void newnode(Snode *&node,int x)
  {
    node=++P;node->lch=node->rch=node->p=nil;;node->size=1;node->id=x;
  }
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
inline Snode *pred(Snode *node)
  {
    splay(root,node,nil);
    Snode *last=nil,*now=node->lch;
    while (now!=nil) last=now,now=now->rch;
    return last;
  }
inline Snode *succ(Snode *node)
  {
    splay(root,node,nil);
    Snode *last=nil,*now=node->rch;
    while (now!=nil) last=now,now=now->lch;
    return last;
  }
inline void insert(Snode *node,int k)
  {
    Snode *t1=root->rank(k-1),*t2=root->rank(k);
    splay(root,t2,nil);splay(root,t1,root);
    root->lch->set_r(node);root->lch->update();root->update();
  }
inline void remove(Snode *&node)
  {
    Snode *t1=pred(node),*t2=succ(node);
    splay(root,t2,nil);splay(root,t1,root);
    root->lch->set_r(nil);root->lch->update();root->update();
    node=nil;
  }
inline int order(Snode *node)
  {
    splay(root,node,nil);return root->lch->size+1;
  }
int main()
  {
    nil->id=-1;
    newnode(ld,0);newnode(rd,0);
    root=rd;rd->set_l(ld);ld->update();rd->update();
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
      {
        scanf("%d",&x);Snode *tmp=pred(rd);
        splay(root,rd,nil);splay(root,tmp,root);
        newnode(pos[x],x);root->lch->set_r(pos[x]);
        root->lch->update();root->update();
        splay(root,pos[x],nil);
      }
    for (int i=1;i<=m;++i)
      {
        do opt=getchar();while (opt=='\n' || opt==' ');
        do ch=getchar();while (ch!=' ');
        if (opt=='T') scanf("%d",&x),remove(pos[x]),newnode(pos[x],x),insert(pos[x],2);
        if (opt=='B') scanf("%d",&x),remove(pos[x]),newnode(pos[x],x),insert(pos[x],n+1);
        if (opt=='I') scanf("%d%d",&x,&y),z=order(pos[x]),remove(pos[x]),newnode(pos[x],x),insert(pos[x],z+y);
        if (opt=='A') scanf("%d",&x),printf("%d\n",order(pos[x])-2);
        if (opt=='Q') scanf("%d",&x),printf("%d\n",root->rank(x+1)->id);
      }
  }      