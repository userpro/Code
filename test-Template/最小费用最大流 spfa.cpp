//h2668
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=1500,M=100000,L=1000000,inf=999999999;
struct Edge 
  {
    int u,v,w,d;
    Edge *next,*other;
  } e[M],*point[N],*P=e,*pre[N];
inline void Add_Edge(int a,int b,int c,int d)
  {
    Edge *Q=++P;++P;
    Q->u=a;Q->v=b;Q->w=c;Q->d=d;Q->next=point[a];Q->other=P;point[a]=Q;
    P->u=b;P->v=a;P->w=0;P->d=-d;P->next=point[b];P->other=Q;point[b]=P;
  }
int S,T,tot,f[N],flow=0,mincost=0,Q[L];
bool v[N];
bool Found()
  {
    memset(f,127,sizeof(f));int h,t;
    f[S]=0;v[S]=true;pre[S]=NULL;
    for (Q[h=t=1]=S;h<=t;++h)
      {
        v[Q[h]]=false;
        for (Edge *j=point[Q[h]];j;j=j->next)
          if (j->w && f[j->u]+j->d<f[j->v])
            {
              f[j->v]=f[j->u]+j->d;pre[j->v]=j;
              if (!v[j->v]) v[Q[++t]=j->v]=true;
            }
      }
    return f[T]<inf;
  }
void Get()
  {
    flow=0;mincost=0;
    while (Found())
      {
        int nowflow=inf;
        for (int i=T;pre[i];i=pre[i]->u)
          nowflow=min(nowflow,pre[i]->w);
        mincost+=nowflow*f[T];flow+=nowflow;
        for (int i=T;pre[i];i=pre[i]->u)
          pre[i]->w-=nowflow,pre[i]->other->w+=nowflow;
      }
  }
const int dx[8]={-1,-1,0,1,1,1,0,-1},dy[8]={0,1,1,1,0,-1,-1,-1};
char a[41][41],b[41][41];
int n,m,sum=0,c[41][41];
inline int Pos(int x,int y) {return (x-1)*m+y;}
inline int Pos_In(int x,int y) {return n*m+(x-1)*m+y;}
inline int Pos_Out(int x,int y) {return 2*n*m+(x-1)*m+y;}
void Build()
  {
    tot=3*n*m;S=++tot;T=++tot;
    for (int i=1;i<=n;++i)
      for (int j=1;j<=m;++j)
        {
          if (a[i][j]=='1') Add_Edge(S,Pos(i,j),1,0);
          if (b[i][j]=='1') Add_Edge(Pos(i,j),T,1,0);
        }
    for (int i=1;i<=n;++i)
      for (int j=1;j<=m;++j)
        {
          int l1,l2;
          if (a[i][j]==b[i][j]) l1=l2=c[i][j]/2;
          else
            if (a[i][j]=='1') l1=c[i][j]/2,l2=(c[i][j]+1)/2;
            else l1=(c[i][j]+1)/2,l2=c[i][j]/2;
          Add_Edge(Pos_In(i,j),Pos(i,j),l1,0);
          Add_Edge(Pos(i,j),Pos_Out(i,j),l2,0);
        }
    for (int i=1;i<=n;++i)
      for (int j=1;j<=m;++j)
        for (int k=0;k<8;++k)
          {
            int x=i+dx[k],y=j+dy[k];
            if (x && y && x<=n && y<=m) 
              Add_Edge(Pos_Out(i,j),Pos_In(x,y),inf,1);
          }
  }
int main()
  {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
      {
        scanf("\n");
        for (int j=1;j<=m;++j) a[i][j]=getchar();
      }
    for (int i=1;i<=n;++i)
      {
        scanf("\n");
        for (int j=1;j<=m;++j) b[i][j]=getchar();
      }
    for (int i=1;i<=n;++i)
      {
        scanf("\n");
        for (int j=1;j<=m;++j) c[i][j]=getchar()-'0';
      }
    int tmp=0;
    for (int i=1;i<=n;++i)
      for (int j=1;j<=m;++j)
        {
          if (a[i][j]=='1') ++sum;
          if (b[i][j]=='1') ++tmp;
        }
    if (sum!=tmp) {puts("-1");return 0;}
    Build();
    Get();
    if (flow!=sum) puts("-1");else printf("%d\n",mincost);
  }