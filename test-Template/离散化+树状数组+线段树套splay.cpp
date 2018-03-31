//h2141
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int N=20012,K=400000;
int n,m,a[N],ans=0;


namespace Discrete
  {
    int x[N],tot=0,past[N];
    int Find(int k)
      {
        int l=1,r=tot;
        while (l<=r)
          {
            int mid=(l+r)>>1;
            if (past[mid]==k) return mid;
            if (past[mid]<k) l=mid+1;else r=mid-1;
          }
      }
    void Solve()
      {
        for (int i=1;i<=n;++i) x[i]=a[i];
        sort(x+1,x+n+1);
        for (int i=1;i<=n;++i)
          if (i==1 || x[i]!=x[i-1]) past[++tot]=x[i];
        for (int i=1;i<=n;++i) a[i]=Find(a[i]);
      }
  }
namespace Bit
  {
    int c[N];
    inline int lowbit(int k) {return k&(-k);}
    inline void Add(int k,int t)
      {
        while (k<=n) c[k]+=t,k+=lowbit(k);
      }
    inline int Sum(int k)
      {
        int ans=0;while (k) ans+=c[k],k-=lowbit(k);return ans;
      }
    void Solve()
      {
        memset(c,0,sizeof(c));
        for (int i=1;i<=n;++i)
          ans+=i-1-Sum(a[i]),Add(a[i],1);
      }
  }
namespace Tree_In_Tree
  {
    struct Snode
      {
        Snode *lch,*rch,*p;
        int size,key;
        inline void Update() {size=lch->size+rch->size+1;}
        inline bool Is_lch() {return this==p->lch;}
        inline void Set_lch(Snode *x) {lch=x;x->p=this;}
        inline void Set_rch(Snode *x) {rch=x;x->p=this;}
        inline void L()
          {
            Snode *fa=p;
            if (fa->Is_lch()) fa->p->Set_lch(this);
              else fa->p->Set_rch(this);
            fa->Set_rch(lch);Set_lch(fa);fa->Update();
          }
        inline void R()
          {
            Snode *fa=p;
            if (fa->Is_lch()) fa->p->Set_lch(this);
              else fa->p->Set_rch(this);
            fa->Set_lch(rch);Set_rch(fa);fa->Update();
          }
        inline int Find_Less(int x)
          {
            if (key==-1) return 0;
            if (key>=x) return lch->Find_Less(x);
              else return rch->Find_Less(x)+lch->size+1;
          }
      } T[K],*P,*nil=T;
    inline void Newnode(Snode *&node,int x)
      {
        node=++P;node->lch=node->rch=nil;
        node->size=1;node->key=x;
      }
    inline void Splay(Snode *&root,Snode *x,Snode *y)
      {
        while (x->p!=y)
          {
            if (x->p->p==y)
              {
                if (x->Is_lch()) x->R();else x->L();break;
              }
            if (x->p->Is_lch())
              if (x->Is_lch()) x->p->R(),x->R();
                else x->L(),x->R();
            else
              if (x->Is_lch()) x->R(),x->L();
                else x->p->L(),x->L();
          }
        x->Update();if (y==nil) root=x;
      }
    inline void Insert(Snode *&root,int x)
      {
        Snode *fa=nil,*t=root;
        while (t!=nil)
          {
            fa=t;++t->size;
            if (x<t->key) t=t->lch;else t=t->rch;
          }
        Newnode(t,x);
        if (x<fa->key) fa->Set_lch(t);else fa->Set_rch(t);
        Splay(root,t,nil);
      }
    inline void Remove(Snode *&root,int x)
      {
        Snode *t=root;
        while (t->key!=x)
          if (t->key<x) t=t->rch;else t=t->lch;
        Splay(root,t,nil);
        if (root->lch==nil) 
          {
            root=root->rch;root->p=nil;return;
          }
        Snode *past=nil;
        for (Snode *t=root->lch;t!=nil;t=t->rch) past=t;
        Splay(root,past,root);
        past->p=nil;past->Set_rch(root->rch);
        root=past;root->Update();
      }
    struct Xnode
      {
        Xnode *lch,*rch;
        Snode *root;
        int l,r;
        int Find_Less(int left,int right,int d)
          {
            if (left>right) return 0;
            if (left<=l && r<=right) return root->Find_Less(d);
            int mid=(l+r)>>1,ans=0;
            if (left<=mid) ans+=lch->Find_Less(left,right,d);
            if (right>mid) ans+=rch->Find_Less(left,right,d);
            return ans;
          }
        void Change(int k,int past,int now)
          {
            Remove(root,past);Insert(root,now);
            if (l==r) return;
            int mid=(l+r)>>1;
            if (k<=mid) lch->Change(k,past,now);
              else rch->Change(k,past,now);
          }
      } X[N*2],*Q,*root;
    void Build(Xnode *&node,int left,int right)
      {
        node=Q++;node->l=left;node->r=right;node->root=nil;
        for (int i=left;i<=right;++i) 
          Insert(node->root,a[i]);
        if (left==right) return;
        int mid=(left+right)>>1;
        Build(node->lch,left,mid);
        Build(node->rch,mid+1,right);
      }
    void Solve() 
      {
        Q=X;P=T;nil->key=-1;
        Build(root,1,n);
      }
  }
int main()
  {
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    Discrete::Solve();
    Bit::Solve();
    Tree_In_Tree::Solve();
    printf("%d\n",ans);
    scanf("%d",&m);int x,y;
    for (int i=1;i<=m;++i)
      {
        scanf("%d%d",&x,&y);int nx=a[y],ny=a[x];
        ans-=x-1-Tree_In_Tree::root->Find_Less(1,x-1,a[x]+1);
        ans-=Tree_In_Tree::root->Find_Less(x+1,n,a[x]);
        ans+=x-1-Tree_In_Tree::root->Find_Less(1,x-1,nx+1);
        ans+=Tree_In_Tree::root->Find_Less(x+1,n,nx);
        Tree_In_Tree::root->Change(x,a[x],nx);a[x]=nx;
        ans-=y-1-Tree_In_Tree::root->Find_Less(1,y-1,a[y]+1);
        ans-=Tree_In_Tree::root->Find_Less(y+1,n,a[y]);
        ans+=y-1-Tree_In_Tree::root->Find_Less(1,y-1,ny+1);
        ans+=Tree_In_Tree::root->Find_Less(y+1,n,ny);
        Tree_In_Tree::root->Change(y,a[y],ny);a[y]=ny;
        printf("%d\n",ans);
      }
  }