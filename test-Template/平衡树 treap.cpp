//t1728
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>

using namespace std;

const int N=100012,inf=2147483647;
int l[N],r[N],size[N],e[N],d[N],tot=0,root=0,n,opt,x;

void left(int &root)
  {
    int next=r[root];
    r[root]=l[next];
    l[next]=root;
    size[next]=size[root];
    size[root]=size[l[root]]+size[r[root]]+1;
    root=next;
  }
void right(int &root)
  {
    int next=l[root];
    l[root]=r[next];
    r[next]=root;
    size[next]=size[root];
    size[root]=size[l[root]]+size[r[root]]+1;
    root=next;
  }
void insert(int &root,int x)
  {
    if (!root)
      {
        root=++tot,l[root]=0,r[root]=0,size[root]=1,
        d[root]=x,e[root]=rand()+rand()+rand()+1;
        return;
      }
    ++size[root];
    if (x<d[root])
      {
        insert(l[root],x);
        if (e[l[root]]>e[root]) right(root);
      }
    else
      {
        insert(r[root],x);
        if (e[r[root]]>e[root]) left(root);
      }
  }
void del(int &root,int x)
  {
    --size[root];
    if (x<d[root]) del(l[root],x);
    if (x>d[root]) del(r[root],x);
    if (x==d[root])
      {
        if (!size[root])
          {
            root=0;return;
          }
        if (e[l[root]]>e[r[root]]) right(root),del(r[root],x);
          else left(root),del(l[root],x);
      }
  }
int search(int root,int x,int sum)
  {
    if (!root) return inf;
    if (d[root]==x) 
      return min(search(l[root],x,sum),sum+size[l[root]]+1);
    if (d[root]<x) return search(r[root],x,sum+size[l[root]]+1);
    if (d[root]>x) return search(l[root],x,sum);
  }
int rank(int root,int x,int sum)
  {
    if (sum+size[l[root]]+1==x) return d[root];
    if (sum+size[l[root]]+1<x)
      return rank(r[root],x,sum+size[l[root]]+1);
    else
      return rank(l[root],x,sum);
  }
int findpred(int root,int x)
  {
    if (!root) return -inf;
    if (d[root]<x) return max(d[root],findpred(r[root],x));
      else return findpred(l[root],x);
  }
int findsucc(int root,int x)
  {
    if (!root) return inf;
    if (d[root]>x) return min(d[root],findsucc(l[root],x));
      else return findsucc(r[root],x);
  }
int main()
  {
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
      {
        scanf("%d%d",&opt,&x);
        if (opt==1) insert(root,x);
        if (opt==2) del(root,x);
        if (opt==3) printf("%d\n",search(root,x,0));
        if (opt==4) printf("%d\n",rank(root,x,0));
        if (opt==5) printf("%d\n",findpred(root,x));
        if (opt==6) printf("%d\n",findsucc(root,x));
      }
  }