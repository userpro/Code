#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

const int N=101;
vector<int> e[N];
int n,m,tim,son[N],rea[N],low[N];
bool v[N];

void clear()
  {
    memset(son,0,sizeof(son));
    memset(low,0,sizeof(low));
    memset(rea,0,sizeof(rea));
    memset(v,false,sizeof(v));
    for (int i=1;i<=n;++i) e[i].clear();
    tim=0;
  }
void dfs(int now)
  {
    rea[now]=low[now]=++tim;
    v[now]=true;
    for (int i=0;i<e[now].size();++i)
      {
        int next=e[now][i];
        if (!v[next])
          {
            dfs(next);
            low[now]=min(low[now],low[next]);
            if (low[next]>=rea[now]) ++son[now];
          }
          else low[now]=min(low[now],rea[next]);
      }
  }
int main()
  {
    while (scanf("%d",&n),n)
      {
        clear();
        int a,b;
        while (scanf("%d",&a),a)
          while (getchar()!='\n') 
            {
              scanf("%d",&b);
              e[a].push_back(b);
              e[b].push_back(a);
            }
        dfs(1);
        --son[1];
        int ans=0;
        for (int i=1;i<=n;++i)
          if (son[i]>0) ++ans;
        printf("%d\n",ans);
      }
  }