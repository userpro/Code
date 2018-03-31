//h2333
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=300001,inf=999999999;
int n,m,a[N],opt[N],x[N],y[N],fa[N],w[N],pos[N],tot=0,next[N],point[N];
char ch;

struct Xnode
  {
    Xnode *lch,*rch;
    int l,r,Max,rest;
    inline void update(){Max=max(lch->Max,rch->Max);}
    inline void add(int x) {Max+=x;rest+=x;}
    inline void pass() {lch->add(rest);rch->add(rest);rest=0;}
    inline void cover(int left,int right,int x)
      {
        if (left<=l && right>=r) {add(x);return;}
        pass();int mid=(l+r)>>1;
        if (left<=mid) lch->cover(left,right,x);
        if (right>mid) rch->cover(left,right,x);
        update();
      }
    inline int ask(int left,int right)
      {
        if (left<=l && right>=r) return Max;
        pass();int mid=(l+r)>>1,ans=-inf;
        if (left<=mid) ans=max(ans,lch->ask(left,right));
        if (right>mid) ans=max(ans,rch->ask(left,right));
        return ans;
      }
  } X[N*2],*P=X,*root;
inline void build(Xnode *&node,int left,int right)
  {
    node=P++;node->l=left;node->r=right;
    int mid=(left+right)>>1;
    if (left==right) {node->Max=node->rest=a[w[mid]];return;}
    build(node->lch,left,mid);
    build(node->rch,mid+1,right);
    node->update();
  }
int find(int k)
  {
    if (fa[k]==k) return k;
    return fa[k]=find(fa[k]);
  }
int main()
  {
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]),fa[i]=point[i]=i,next[i]=0;
    scanf("%d",&m);
    for (int i=1;i<=m;++i)
      {
        scanf("\n%c",&ch);
        if (ch=='U') 
          {
            opt[i]=1,scanf("%d%d",&x[i],&y[i]);
            int p=find(x[i]),q=find(y[i]);
            if (p!=q)
              {
                fa[q]=p;next[point[p]]=q;
                point[p]=point[q];
              }
          }
        if (ch=='A')
          {
            ch=getchar();
            if (ch=='1') opt[i]=2,scanf("%d%d",&x[i],&y[i]);
            if (ch=='2') opt[i]=3,scanf("%d%d",&x[i],&y[i]);
            if (ch=='3') opt[i]=4,scanf("%d",&x[i]);
          }
        else 
          {
            ch=getchar();
            if (ch=='1') opt[i]=5,scanf("%d",&x[i]);
            if (ch=='2') opt[i]=6,scanf("%d",&x[i]);
            if (ch=='3') opt[i]=7;
          }
      }
    for (int i=1;i<=n;++i)
      if (fa[i]==i)
        for (int j=i;j;j=next[j]) w[++tot]=j,pos[j]=tot;
    build(root,1,n);
    for (int i=1;i<=n;++i) fa[i]=point[i]=i,next[i]=0;
    for (int i=1;i<=m;++i) 
      {
        if (opt[i]==1) 
          {
            int p=find(x[i]),q=find(y[i]);
            if (p!=q)
              {
                fa[q]=p;next[point[p]]=q;
                point[p]=point[q];
              }
          }
        if (opt[i]==2) root->cover(pos[x[i]],pos[x[i]],y[i]);
        if (opt[i]==3) root->cover(pos[find(x[i])],pos[point[find(x[i])]],y[i]);
        if (opt[i]==4) root->cover(1,n,x[i]);
        if (opt[i]==5) printf("%d\n",root->ask(pos[x[i]],pos[x[i]]));
        if (opt[i]==6) printf("%d\n",root->ask(pos[find(x[i])],pos[point[find(x[i])]]));
        if (opt[i]==7) printf("%d\n",root->ask(1,n));
      }
  }