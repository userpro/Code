//t1816
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=1001;
int n,m,k,a,b,linked[N],ans=0,v[N];
struct edge {int u,v;edge *next;} e[N*N],*point[N],*P=e;
inline void add_edge(int a,int b)
  {
    P->u=a;P->v=b;P->next=point[a];point[a]=P++;
  }
bool find(int root,int now)
  {
    for (edge *j=point[now];j;j=j->next)
      if (v[j->v]!=root)
        {
          v[j->v]=root;
          if (!linked[j->v]||find(root,linked[j->v])) 
            {
              linked[j->v]=now;
              return true;
            }
        }
    return false;
  }
int main()
  {
    scanf("%d%d%d",&m,&n,&k);
    for (int i=1;i<=k;++i)
      scanf("%d%d",&a,&b),add_edge(a,b);
    for (int i=1;i<=m;++i) 
      if (find(i,i)) ++ans;
    printf("%d\n",m+n-ans);
  }