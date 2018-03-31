//h2337
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=105,M=20012;
int n,m,du[N];
double a[N][N],x[N],b[N],ans=0;
struct Edge {int u,v,w;Edge *next;} e[M],*point[N],*P=e;
inline void Add_Edge(int a,int b,int c)
  {
    P->u=a;P->v=b;P->w=c;P->next=point[a];point[a]=P++;++du[a];
  }
void Xiao(int p,int q)
  {
    double k=a[q][p]/a[p][p];
    for (int i=1;i<=n;++i) a[q][i]=a[p][i]*k-a[q][i];
    b[q]=b[p]*k-b[q];
  }
bool Jie(int k)
  {
    double ans=b[k];
    for (int i=k+1;i<=n;++i) ans-=x[i]*a[k][i];
    x[k]=ans/a[k][k];
    return true;
  }
void Gauss()
  {
    for (int i=1;i<=n;++i)
      {
        int p=i;
        for (int j=i+1;j<=n;++j)
          if (fabs(a[j][i])>fabs(a[p][i])) p=j;
        swap(a[i],a[p]);swap(b[i],b[p]); 
        for (int j=i+1;j<=n;++j) Xiao(i,j);
      }
    for (int i=n;i;--i) if (!Jie(i)) return;
  }

int main()
  {
    scanf("%d%d",&n,&m);
    for (int i=1,u,v,w;i<=m;++i)
      {
        scanf("%d%d%d",&u,&v,&w);
        Add_Edge(u,v,w);if (u!=v) Add_Edge(v,u,w);
      }
    for (int l=0;l<31;++l)
      {
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(x,0,sizeof(x));
        for (int i=1;i<=n;++i) a[i][i]=1;
        for (int i=1;i<n;++i)
          for (Edge *j=point[i];j;j=j->next)
            if ((j->w>>l)&1) a[i][j->v]+=1.0/du[i],b[i]+=1.0/du[i];
              else a[i][j->v]-=1.0/du[i];
        Gauss();
        ans+=x[1]*(1<<l);
      }
    printf("%.3lf\n",ans);
  }