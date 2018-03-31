//paint
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=100001;
int n,m,c[N],Q[N],d[N],a,b,color,size[N],belong[N],tot[N],up[N],order[N],fa[N],num=0;
struct edge {int u,v;edge *next;} e[N*2],*R=e,*point[N];
inline void add_edge(int a,int b)
  {
    R->u=a;R->v=b;R->next=point[a];point[a]=R++;
  }
bool select[N];
char ch;
struct message{int lc,rc,sum;};
struct Xnode
  {
    Xnode *lch,*rch;
    int l,r,flag;
    message c;
    inline void update()
      {
        c.sum=lch->c.sum+rch->c.sum-(lch->c.rc==rch->c.lc);
        c.lc=lch->c.lc;c.rc=rch->c.rc;
      }
    inline void paint(int color)
      {
        c.sum=1;c.lc=c.rc=flag=color;
      }
    inline void pass()
      {
        if (flag==-1) return;
        lch->paint(flag);rch->paint(flag);
        flag=-1;
      }
    inline void change(int left,int right,int color)
      {
        if (left<=l && right>=r) {paint(color);return;}
        pass();int mid=(l+r)>>1;
        if (left<=mid) lch->change(left,right,color);
        if (right>mid) rch->change(left,right,color);
        update();
      }
    inline message ask(int left,int right)
      {
        if (left<=l && right>=r) return c;
        pass();int mid=(l+r)>>1;
        if (right<=mid) return lch->ask(left,right);
        if (left>mid) return rch->ask(left,right);
        message a=lch->ask(left,right),b=rch->ask(left,right),c;
        c.sum=a.sum+b.sum-(a.rc==b.lc);c.lc=a.lc;c.rc=b.rc;
        return c;
      }
  } X[3*N],*P=X,*root[N];
void build(Xnode *&node,int left,int right)
  {
    node=P++;node->l=left;node->r=right;
    node->c.sum=1;node->c.lc=node->c.rc=0;node->flag=-1;
    if (left==right) return;
    int mid=(left+right)>>1;
    build(node->lch,left,mid);
    build(node->rch,mid+1,right);
    node->update();
  }
void bfs()
  {
    int h,t,x;fa[1]=0;d[1]=1;
    for (Q[h=t=1]=1;h<=t;++h)
      for (edge *j=point[Q[h]];j;j=j->next)
        if (fa[Q[h]]!=j->v) fa[Q[++t]=j->v]=Q[h],d[j->v]=d[Q[h]]+1;
    memset(select,true,sizeof(select));
    for (int i=t;i;--i)
      {
        int x=Q[i],w=0,maxsize=0;size[x]=1;
        for (edge *j=point[x];j;j=j->next)
          {
            size[x]+=size[j->v];
            if (size[j->v]>maxsize) maxsize=size[j->v],w=j->v;
          }
        select[w]=false;
      }
    for (int i=1;i<=t;++i)
      if (select[x=Q[i]]) 
        belong[x]=++num,tot[num]=1,up[x]=x,order[x]=1;
      else 
        belong[x]=belong[fa[x]],++tot[belong[x]],up[x]=up[fa[x]],order[x]=order[fa[x]]+1;
    for (int i=1;i<=num;++i) build(root[i],1,tot[i]);
    for (int i=1;i<=n;++i) root[belong[i]]->change(order[i],order[i],c[i]);
  }
void query(int x,int y)
  {
    int ans=0;
    message a,b,c;a.lc=a.rc=b.lc=b.rc=-1;
    while (belong[x]!=belong[y])
      if (d[up[fa[up[x]]]]>d[up[fa[up[y]]]])
        c=root[belong[x]]->ask(1,order[x]),
        ans+=c.sum-(c.rc==a.lc),a=c,x=fa[up[x]];
      else
        c=root[belong[y]]->ask(1,order[y]),
        ans+=c.sum-(c.rc==b.lc),b=c,y=fa[up[y]];
    if (order[x]>order[y])
      c=root[belong[x]]->ask(order[y],order[x]),
      ans+=c.sum-(c.lc==b.lc)-(c.rc==a.lc);
    else
      c=root[belong[y]]->ask(order[x],order[y]),
      ans+=c.sum-(c.lc==a.lc)-(c.rc==b.lc);
    printf("%d\n",ans);
  }
void work(int x,int y,int z)
  {
    while (belong[x]!=belong[y])
      if (d[up[fa[up[x]]]]>d[up[fa[up[y]]]])
        root[belong[x]]->change(1,order[x],z),x=fa[up[x]];
      else 
        root[belong[y]]->change(1,order[y],z),y=fa[up[y]];
    if (order[x]>order[y]) root[belong[x]]->change(order[y],order[x],z);
      else root[belong[x]]->change(order[x],order[y],z);
  }
int main()
  {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i) scanf("%d",&c[i]);
    for (int i=1;i<n;++i) scanf("%d%d",&a,&b),add_edge(a,b),add_edge(b,a);
    bfs(); 
    for (int i=1;i<=m;++i)
      {
        scanf("\n%c",&ch);
        if (ch=='Q') scanf("%d%d",&a,&b),query(a,b);
          else scanf("%d%d%d",&a,&b,&color),work(a,b,color);
      }
  }