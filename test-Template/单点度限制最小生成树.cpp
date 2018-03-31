//poj1639
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

const int N=22,M=401,inf=2147483647;
map<string,int> name;
map<string,int>::iterator it;
struct edge {int u,v,w;} e[M];
int u,v,w,k,l,Min[N][N],f[N],ans,pre[N],num[N],n=0,m,tot=0,c[N][N];
bool linked[N][N],visit[N];
string s;  

inline void init(int &x)
  {
    cin>>s;
    it=name.find(s);
    if (it!=name.end()) x=it->second;
      else x=name[s]=++n;
  }
inline void add_edge(int a,int b,int c)
  {
    ++l;e[l].u=a;e[l].v=b;e[l].w=c;
  }
inline bool cmp(edge a,edge b)
  {
    return a.w<b.w;
  }
int find(int k)
  {
    if (f[k]==k) return k;
    return f[k]=find(f[k]);
  }
void dfs(int k)
  {
    visit[k]=true;
    c[tot][++num[tot]]=k;
    for (int i=1;i<=n;++i) 
      if (linked[k][i] && !visit[i]) dfs(i);
  }
bool find_circle(int k)
  {
    visit[k]=true;
    if (k==0) return true;
    for (int i=1;i<=n;++i)
      if (linked[k][i] && !visit[i]) 
        {
          pre[i]=k;
          if (find_circle(i)) return true;
        }
    visit[k]=false;
    return false;
  }
int main()
  {
    scanf("%d\n",&m);
    memset(Min,255,sizeof(Min));
    name["Park"]=++n;
    for (int i=1;i<=m;++i)
      {
        init(u),init(v),scanf("%d",&w);
        if (u!=1 && v!=1) add_edge(u,v,w);
        if (Min[u][v]==-1) Min[u][v]=Min[v][u]=w;
          else Min[u][v]=Min[v][u]=min(Min[u][v],w);
      }
    scanf("%d",&k);
    sort(e+1,e+l+1,cmp);
    for (int i=1;i<=n;++i) f[i]=i;
    for (int i=1;i<=l;++i)
      {
        int p=find(e[i].u),q=find(e[i].v);
        if (p!=q) ans+=e[i].w,f[p]=q,
          linked[e[i].u][e[i].v]=linked[e[i].v][e[i].u]=true;
      }
    memset(visit,false,sizeof(visit));
    for (int i=2;i<=n;++i)
      if (!visit[i]) ++tot,dfs(i);
    for (int i=1;i<=tot;++i)
      {
        int m=inf,t;
        for (int j=1;j<=num[i];++j)
          if (Min[1][c[i][j]]!=-1 && Min[1][c[i][j]]<m)
            m=Min[1][c[i][j]],t=c[i][j];
        ans+=m;linked[1][t]=linked[t][1]=true;
      }
    for (int i=1;i<=k-tot;++i)
      {
        int delta=0,t;
        for (int j=2;j<=n;++j)
          if (!linked[1][j] && Min[1][j]!=-1)
            {
              memset(visit,false,sizeof(visit));
              memset(pre,0,sizeof(pre));
              find_circle(j);
              int zh=1,m=0,a,b;
              while (zh!=j) 
                {
                  if (Min[zh][pre[zh]]>m)
                    m=Min[zh][pre[zh]],a=zh,b=pre[zh];
                  zh=pre[zh];
                }
              if (m-Min[1][j]>delta) 
                delta=m-Min[1][j],u=a,v=b,t=j;
            }
        if (delta) 
          {
            ans-=delta;
            linked[u][v]=linked[v][u]=false;
            linked[1][t]=linked[t][1]=true;
          }
          else break;
      }
    printf("Total miles driven: %d\n",ans);
  }
    