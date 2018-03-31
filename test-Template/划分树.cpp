//t1253
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int N=100012,H=20;
int n,m,a[N];

void init()
  {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
  }
namespace Partition_tree
  {
    int sum[H][N],tree[H][N];
    struct Tnode
      {
        Tnode *lch,*rch;
        int l,r,dep;
        int ask(int left,int right,int k)
          {
            if (left==l && right==r) return a[left+k-1];
            int t1,t2;
            if (left==l) t1=0;else t1=sum[dep][left-1];t2=sum[dep][right];
            if (t2-t1>=k) return lch->ask(l+t1,l+t2-1,k);
              else
                {
                  int sr=((l+r)>>1)+1;
                  return rch->ask(sr+(left-l-t1),sr+(right-l+1-t2)-1,k-(t2-t1));
                }
          }
      } T[N*2],*root,*P=T;
    void build(Tnode *&node,int left,int right,int d)
      {
        node=P++;node->l=left;node->r=right;node->dep=d;
        if (left==right) return;
        int mid=(left+right)>>1,x=a[mid],lsame=mid-left+1,t1=left-1,t2=mid,same=0;
        for (int i=left;i<=right;++i) if (tree[d][i]<a[mid]) --lsame;
        for (int i=left;i<=right;++i)
          {
            if (i==left) sum[d][i]=0;else sum[d][i]=sum[d][i-1];
            if (tree[d][i]==x) ++same;
            if (tree[d][i]<x || tree[d][i]==x && same<=lsame)
              tree[d+1][++t1]=tree[d][i],++sum[d][i];
            else
              tree[d+1][++t2]=tree[d][i];
          }
        build(node->lch,left,mid,d+1);
        build(node->rch,mid+1,right,d+1);
      }
    void solve()
      {
        for (int i=1;i<=n;++i) tree[0][i]=a[i];
        sort(a+1,a+n+1);build(root,1,n,0);
        int x,y,k;
        for (int i=1;i<=m;++i)
          scanf("%d%d%d",&x,&y,&k),printf("%d\n",root->ask(x,y,k));
      }
  }
int main()
  {
    init();
    Partition_tree::solve();
  }