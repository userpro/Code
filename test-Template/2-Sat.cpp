//h2199
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

const int N=8012;
int n,m;
namespace Two_Sat
  {
    vector<int> path[N],edge[N];
    typedef vector<int>::iterator it;
    char ch1,ch2;
    int tim=0,v[N],Z[N],low[N],rea[N],top=0,id[N],tot=0,ops[N];
    bool vis[N],select[N],flag[N];
    int other(int x) {if (x<=n) return x+n;else return x-n;}
    void Dfs(int now)
      {
        low[now]=rea[now]=++tim;v[now]=1;Z[++top]=now;
        for (it p=path[now].begin();p!=path[now].end();++p)
          {
            if (!v[*p]) Dfs(*p);
            if (v[*p]<2) low[now]=min(low[now],low[*p]);
          }
        if (rea[now]==low[now])
          for (++tot;Z[top+1]!=now;--top) 
            v[Z[top]]=2,id[Z[top]]=tot;
      }
    void Deal(int now)
      {
        vis[now]=true;
        for (it p=edge[now].begin();p!=edge[now].end();++p) Deal(*p);
      }
    void Solve()
      {
        int x,y;
        for (int i=1;i<=m;++i) 
          {
            scanf("\n%d %c %d %c",&x,&ch1,&y,&ch2);
            if (ch1=='N') x+=n;if (ch2=='N') y+=n;
            path[other(x)].push_back(y);
            path[other(y)].push_back(x);
          }
        memset(v,0,sizeof(v));
        for (int i=1;i<=2*n;++i) if (!v[i]) Dfs(i);
        for (int i=1;i<=2*n;++i)
          for (it p=path[i].begin();p!=path[i].end();++p)
            if (id[i]!=id[*p]) 
              edge[id[i]].push_back(id[*p]);
        for (int i=1;i<=n;++i)
          if (id[i]==id[i+n]) {puts("IMPOSSIBLE");return;}
        for (int i=1;i<=2*n;++i) ops[id[i]]=id[other(i)];
        memset(flag,false,sizeof(flag));
        memset(select,true,sizeof(select));
        for (int i=1;i<=tot;++i)
          if (!flag[i])
            {
              flag[i]=true;
              memset(vis,false,sizeof(vis));
              Deal(i);
              if (vis[ops[i]]) select[i]=false;
            }
        for (int i=1;i<=n;++i)
          if (select[id[i]])
            if (select[id[other(i)]]) putchar('?');
            else putchar('Y');
          else putchar('N');
        puts("");
      }
  }
int main()
  {
    scanf("%d%d",&n,&m);
    Two_Sat::Solve();
  }